#include <stdio.h>
#include <string.h>
#include <locale.h>                         // http://mesutpiskin.com/blog/cc-turkce-karakter-kullanmak.html
#define MAX_SIZE 9999

typedef struct{
    int kod;
    char sehir[20];
} sehir_kod;

sehir_kod list[MAX_SIZE];
int static sehir_sayisi=0;

//https://drive.google.com/drive/u/0/folders/0Bw8VB6WrbOkiUW1mdkF0cXlJRmc
//http://scanftree.com/Data_Structure/dijkstra's-algorithm
void dijkstra(int matris[sehir_sayisi][sehir_sayisi], int konum, int hedef)			
{
	int maliyet[sehir_sayisi][sehir_sayisi], mesafe[sehir_sayisi], onceki[sehir_sayisi], ziyaret_edilen[sehir_sayisi], sayac, en_kisa_mesafe, siradaki, i,j;
	
	for(i=0; i<sehir_sayisi; i++)	for(j=0; j<sehir_sayisi; j++)	if(matris[i][j]==0)	maliyet[i][j]=MAX_SIZE;
																		else	maliyet[i][j]=matris[i][j];

	for(i=0; i<sehir_sayisi; i++)
		{
			mesafe[i]=maliyet[konum][i];
			onceki[i]=konum;
			ziyaret_edilen[i]=0;
		}
		
	mesafe[konum]=0;
	ziyaret_edilen[konum]=1;
	sayac=1;
	
	while(sayac<sehir_sayisi-1)
		{
			en_kisa_mesafe=MAX_SIZE;
			for(i=0; i<sehir_sayisi; i++)	if(mesafe[i]<en_kisa_mesafe &&	ziyaret_edilen[i]==0)
												{
													en_kisa_mesafe=mesafe[i];
													siradaki=i;
												}
			ziyaret_edilen[siradaki]=1;
			
			for(i=0; i<sehir_sayisi; i++)	if(ziyaret_edilen[i]==0)	if(en_kisa_mesafe+maliyet[siradaki][i] < mesafe[i])
																		{
																			mesafe[i]=en_kisa_mesafe+maliyet[siradaki][i];
																			onceki[i]=siradaki;
																		}
			sayac++;
		}

		for(i=0; i<sehir_sayisi; i++)	if(i==hedef)
											{
												printf("\n  %s'den %s'ye en kisa mesafe = %d km", list[konum].sehir,list[i].sehir, mesafe[i]);
												printf("\t| Gidis yolu = %s", list[i].sehir);
												j=i;
												do
												{
													j=onceki[j];
													printf(" <-> %s", list[j].sehir);
												}
												while(j!=konum);
											}
											
        printf("\n--------------------------------------------------------------------------------------------");
        printf("------------------------------------\n\n  %s'den diger illere en kisa mesafe(X kendisi):\n", list[konum].sehir);
        
        for(i=0; i<sehir_sayisi; i++)
			{	
				if(i==konum)
		    		printf("\nX %s'den %s'ye en kisa mesafe = %d km", list[konum].sehir,list[i].sehir, mesafe[i]);
				else
					printf("\n  %s'den %s'ye en kisa mesafe = %d km", list[konum].sehir,list[i].sehir, mesafe[i]);
				printf("\t| Gidis yolu = %s", list[i].sehir);
				j=i;
				do
				{
					j=onceki[j];
					printf(" <-> %s", list[j].sehir);
				}
				while(j!=konum);
			}
			
        printf("\n");
}

int main()
{
    setlocale(LC_ALL, "Turkish");		// http://mesutpiskin.com/blog/cc-turkce-karakter-kullanmak.html

    int index1,index2, hedef, konum, b, a=0, mesafe=0;
    char *str, *str2, tut[MAX_SIZE];

    FILE *txt = fopen("sehir kod.txt", "r");
	FILE *txt2 = fopen("sehir mesafe.txt", "r");

    str = fgets(tut,MAX_SIZE,txt);
    str = fgets(tut,MAX_SIZE,txt);

    while(str != NULL){
        str2 = strtok(tut, "-");
        sscanf(str2,"%d", &list[a].kod);
        strcpy(list[a].sehir, str2);

        str2 = strtok(NULL, "\n" );
        sscanf(str2,"%d", &list[a].kod);

        sehir_sayisi++;
        a++;
        str = fgets(tut,MAX_SIZE,txt);
    }

    int matris[sehir_sayisi][sehir_sayisi];

    for(a=0; a<sehir_sayisi;a++)    for(b=a;b<sehir_sayisi; b++)
                                        {
                                            matris[a][b]=NULL;
                                            matris[b][a]=NULL;
                                        }

    str = fgets(tut,MAX_SIZE,txt2);
    str = fgets(tut,MAX_SIZE,txt2);

    while(str != NULL){
        str2 = strtok(tut, "-");
        for(a=0; a<sehir_sayisi; a++)   if(strcmp(str2,list[a].sehir) == 0) index1 = a;

		str2 = strtok(NULL, "-");
		for(b=0; b<sehir_sayisi; b++)   if(strcmp(str2,list[b].sehir) == 0) index2 = b;

        str2 = strtok(NULL, "\n" );
        sscanf(str2,"%d", &mesafe);

		matris[index1][index2] = mesafe;
		matris[index2][index1] = mesafe;

        str = fgets(tut,MAX_SIZE,txt2);
    }

    /*** MATRÝSÝN DOÐRULUÐUNUN KANITI ***
    for(a=0; a<sehir_sayisi;a++){
        for(b=0;b<sehir_sayisi; b++){
            if(a==b){
                matris[a][b]=0;
                matris[b][a]=0;
            }
            printf("%d ", matris[a][b]);
        }
        printf("\n");
    }
    ** MATRÝSÝN DOÐRULUÐUNUN KANITI **/

    printf("\t\t\tTALHA SARIOGLU-140201135\n\t\t PROLAB2_PROJE1: EN KISA MESAFEYI BUL\n\n  Sehirler ve Kodlari:\n");

    for(a=0; a<sehir_sayisi; a++)   printf("%2d - %s\t", list[a].kod,list[a].sehir);
    
	do
	{	
	    printf("\n\n  Lutfen ilk sehirin kodunu giriniz: ");        scanf("%d", &konum);
	    printf("  Lutfen gidilecek sehirin kodunu giriniz: ");    scanf("%d", &hedef);
	}
	while(konum>sehir_sayisi || hedef>sehir_sayisi);
	
    dijkstra(matris, konum-1, hedef-1);

    fclose(txt);    fclose(txt2);       return 0;
 }

