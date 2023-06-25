#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define TAILLE_TABLEAU 8 //mayın tarlasının kaça kaç matris olduğu
#define NORMALE 7 // mayın sayım
#define GAGNER 1 //kazandım 
#define PERDU -1 //kaybettim 
#define CONTINUE 0 //Oyuna devam ediyorum 

//Variables Global
int soustab[TAILLE_TABLEAU+2][TAILLE_TABLEAU+2];
char tab[TAILLE_TABLEAU+2][TAILLE_TABLEAU+2];
int nb_mine;
int y=0;
int d_count=0;

//projede kullanılacak fonksiyonlar:
void creer_soustableau(); //alt tablomu oluşturmamı sağlar.
void initializer_tableau();// ilk olarak tablomy initialiser etmemi sağlar 
void afficher_soustableau();// alt tablomu bastırmamı sağlar 
void afficher_tableau();// tablomu bastırmamı sağlar 
void placer_mines();// mayınları yerleştirir.
int verifiermatchgagner();// kazanıp kazanmadığımı kontrol eden bir fonksiyon 
void explorer();// mayın tarlamda ne var ne yok keşif ediyor 
int creuser(int ligne, int  colonne);// mayın tarlasının içindeki istediğim koordinatı açmamı sağlar.

int main()
{
    int ligne,colonne;
    int ilerleme;
    int yeniden;
    char action; //hangi harf
    printf("Mayın tarlası oyunumuza hoşgeldiniz\n");
    creer_soustableau();
    initializer_tableau();
    do
    {
        afficher_soustableau();
        printf("\n");
        printf("Lütfen şu formatta giriniz : c,ligne,colonne; d,ligne,colonne; e,ligne,colonne\n");
        scanf("%c,%d,%d",&action,&ligne,&colonne);
        printf("\n");

        if(action == 'c')
        {
            ilerleme=creuser(ligne,colonne);
        }
        else if(action == 'd')
        {
            if(nb_mine > d_count)
            {
                d_count++;
                tab[ligne][colonne] = 'D';
                ilerleme=verifiermatchgagner();
            }
        }
        else if(action == 'e')
        {
            if(d_count > 0)
            {
                d_count--;
            }
            tab[ligne][colonne] = '#';
            ilerleme=creuser(ligne,colonne);
        }


        if(ilerleme == PERDU)
        {
            printf("Oyunu kaybettiniz !\n");
            afficher_soustableau();
            printf("Oyunu tekrar oynamak ister misiniz? : [1-Evet][2-Hayır] \n");
            scanf("%d",&yeniden);
            switch(yeniden)
            {
            case 0:
                printf("Teşekkürler görüşmek üzere <3\n");
                return 0;
                break;
            case 1:
                d_count = 0;
                ilerleme=CONTINUE;
                creer_soustableau();
                initializer_tableau(); 
                break;
            default:
                printf("Yanlış bir değer girdiniz\n");
                break;
            
            }
        }

        if(ilerleme==GAGNER)
        {
            printf("TEBRİKLER OYUNU BAŞARI İLE KAZANDINIZ !!!\n");
            afficher_soustableau();
             printf("Oyunu tekrar oynamak ister misiniz? : [1-Evet][2-Hayır] \n");
            scanf("%d",&yeniden);
            switch(yeniden)
            {
            case 0:
                printf("Teşekkürler görüşmek üzere <3\n");
                return 0;
                break;
            case 1:
                d_count = 0;
                ilerleme=CONTINUE;
                creer_soustableau();
                initializer_tableau(); 
                break;
            default:
                printf("Yanlış bir değer girdiniz\n");
                break;
            
            }
        }



    } while (1);
    
    return 0;
}

void creer_soustableau()
{
    int i,j,nb_mine;
    for (i=0 ; i <= TAILLE_TABLEAU +1 ; i++)
    {
       for ( j = 0 ; j <= TAILLE_TABLEAU +1 ; j++)
       {
           soustab[i][j]=0;
       }
       
    }

    for(i=0;i<=TAILLE_TABLEAU+1;i++)
    {
        soustab[i][0]=1;
        soustab[i][TAILLE_TABLEAU+1]=1;
    }

    for(j=0;j<=TAILLE_TABLEAU;j++)
    {
        soustab[0][j]=1;
        soustab[TAILLE_TABLEAU+1][j]=1;
    }
    nb_mine=NORMALE;
    placer_mines();

}

void initializer_tableau()
{
    int i,j;
    for (i=0 ; i <= TAILLE_TABLEAU +1 ; i++)
    {
       for ( j = 0 ; j <= TAILLE_TABLEAU +1 ; j++)
       {
           tab[i][j]='#';
       }
       
    }

    for(i=0;i<=TAILLE_TABLEAU+1;i++)
    {
        tab[i][0]='*';
        tab[i][TAILLE_TABLEAU+1]='*';
    }

    for(j=0;j<=TAILLE_TABLEAU;j++)
    {
        tab[0][j]='*';
        tab[TAILLE_TABLEAU+1][j]='*';
    }
}

void afficher_soustableau()
{
    int i,j;
    printf("\n");

    for(i=1;i<=TAILLE_TABLEAU;i++)
    {
        printf("%3d",i);
    }
    printf("\n");

    for(i=1;i<=TAILLE_TABLEAU;i++)
    {
        for(j=1;j<=TAILLE_TABLEAU;j++)
        {
            printf("%3c",tab[i][j]);
        }
        printf("  |%d",i);
        printf("\n");
    }

    for(i=0;i<=TAILLE_TABLEAU;i++)
    printf("---");
}

void placer_mines()
{
    srand(time(NULL));
    nb_mine=NORMALE;
    int i,j,k,p,ligne,colonne;

    for(i=1;i<=nb_mine;i++)
    {
        ligne=1+rand()%TAILLE_TABLEAU;
        colonne=1+rand()%TAILLE_TABLEAU;

        if(soustab[ligne][colonne] == -1)
            i--;
        soustab[ligne][colonne]=-1;
        for(k= -1;k<=1;k++)
        {
            for(p= -1;p<=1;p++)
            {
                if(soustab[i][j] == -1 )
                {
                    if(soustab[ligne+k][colonne+p] != -1) //komşusu bomba değilse 
                    {
                        soustab[ligne+k][colonne]++;
                    }
                }
            }
        }
    }

}

int creuser(int ligne, int  colonne)
{
    int x=0;
    if(soustab[ligne][colonne] == -1)                 //bomba ise
    {
        x=PERDU;
    }

    else if(soustab[ligne][colonne] > 0)                   //bomba değilse ve çevresinde bomba varsa 
    {
        tab[ligne][colonne]=('0'+soustab[ligne][colonne]);  //Aç
        // x=verifiermatchgagner();
        x=CONTINUE;
    }
    else
    {
        explorer(ligne,colonne);   //eğer komşularında da bomba yoksa açarak devam ederiz
    }

    return x;
}

void explorer(int ligne, int colonne)
{
    int i,j;
    tab[ligne+i][colonne+j]=('0'+soustab[ligne+i][colonne+j]);       //recursive bir fonk. olduğu için atamamı sürekli yapmam gerekiyor

    for(i= -1 ; i<= 1; i++)            //ilk for döngüsü satırdaki komşulara bakmamı sağlayacak
    {
        for(j =-1 ;j<= 1; j++)
        {
            if(soustab[ligne+i][colonne+j] > 0  && tab[ligne+i][colonne+j] == '#')
            {
                tab[ligne+i][colonne+j]=('0'+soustab[ligne+i][colonne+j]);
            }
            else if(soustab[ligne+i][colonne+j] == 0 && tab[ligne+i][colonne+j] == '#')
            {
                explorer(ligne+i,colonne+j);  //recursive bir fonk. kendi kendini sürekli çağıracak 
            }
        }
    }
}

int verifiermatchgagner()
{
    int i,j;
    int status;

    for(i = 1; i <= TAILLE_TABLEAU ; i++)
    {
        for(j = 1; j<=TAILLE_TABLEAU ; j++)
        {
            if(tab[i][j] == 'D')
            {
                if(soustab[i][j] == -1)
                {
                    y++;
                }
            }
        }
    }

    if(y == NORMALE)
    {
        status=GAGNER;
    }
    else  
    {
        status=CONTINUE;
    }

    return status;
    
}
