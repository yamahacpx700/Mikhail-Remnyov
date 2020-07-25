#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdio>
#include <iomanip>

using namespace std;


#define B 2 // черная шашка
#define W 1 // белая шашка
#define F 3 // выход за границу

char alephbeth[] = "ABCDEFGH";

/*
// печатаем все символы Юникод
void write_Simbol(void){
    char c;
    int j = -128;

    for(c = -128; c < 127; c++)
    {
     printf("%d = %c  ",j,c);
     printf("\n");
     j++;
    }
    printf("\n");
} */



    //стартовая позиция
           int pos [10*10]={F, F, F, F, F, F, F, F, F, F,
                            F, 0, 0, 0, 0, B, B, B, B, F,
                            F, 0, 0, 0, 0, B, B, B, B, F,
                            F, 0, 0, 0, 0, B, B, B, B, F,
                            F, 0, 0, 0, 0, 0, 0, 0, 0, F,
                            F, 0, 0, 0, 0, 0, 0, 0, 0, F,
                            F, W, W, W, W, 0, 0, 0, 0, F,
                            F, W, W, W, W, 0, 0, 0, 0, F,
                            F, W, W, W, W, 0, 0, 0, 0, F,
                            F, F, F, F, F, F, F, F, F, F};
    //вес каждой клетки в массиве для поиска лучшего хода
       /*  int stTab [10*10]={0, 0,    0,    0,    0,    0,   0,   0,   0,  0,
                            0, 70,   60,   50,   40,   4,   3,   2,   1,  0,
                            0, 80,   70,   60,   50,   5,   4,   3,   2,  0,
                            0, 90,   80,   70,   60,   6,   5,   4,   3,  0,
                            0, 100,  90,   80,   70,   60,  50,  40,  30, 0,
                            0, 110,  100,  90,   80,   70,  60,  50,  40, 0,
                            0, 120,  110,  100,  90,   80,  70,  60,  50, 0,
                            0, 130,  120,  110,  100,  90,  80,  70,  60, 0,
                            0, 140,  130,  120,  110,  100, 90,  80,  70, 0,
                            0, 0,    0,    0,    0,    0,   0,   0,   0,  0};
        */
           int stTab [10*10]={0, 0,    0,    0,    0,    0,   0,   0,   0,  0,
                                       0, 8,   7,   6,   5,   4,   3,   2,   1,  0,
                                       0, 16,   15,   14,   13,   12,   11,   10,   9,  0,
                                       0, 23,   22,   21,   20,   19,   18,   17,   10,  0,
                                       0, 29,  28,   27,   26,   25,  24,  18,  11, 0,
                                       0, 34,  33,  32,   31,   30,  25,  19,  12, 0,
                                       0, 404,  403,  402,  401,   31,  26,  20,  13, 0,
                                       0, 407,  406,  405,  402,  32,  27,  21,  14, 0,
                                       0, 409 ,  408,  406,  403,  33, 28,  22,  15, 0,
                                       0, 0,    0,    0,    0,    0,   0,   0,   0,  0};
      // стартовая позиция черных шашек
      int pieceTabB[12]={16, 17, 18, 19,
                         26, 27, 28, 29,
                         36, 37, 38, 39};
      //стартовая позиция белых шашек
      int pieceTabW[12]={61, 62, 63, 64,
                         71, 72, 73, 74,
                         81, 82, 83, 84};
      //номера конечной позиции для черных
      int EndTabB[12]={61, 62, 63, 64,
                       71, 72, 73, 74,
                       81, 82, 83, 84};
      int EndTabW[12]={16, 17, 18, 19,
                       26, 27, 28, 29,
                       36, 37, 38, 39};
      //приращение при движении шашки
      int delTab[4]={-1, 1, -10, 10};
      // описатель перемещения
      typedef struct{
          int source, dest;}TMove,*PMove;
      // /////////тип - множество///////////
      typedef union {
          unsigned char data[16];
          long __data[4];
      }TSet,*PSet;
      //обнуляет множество
#define Clear(set)\
    (set).data[0]=0; (set).data[1]=0; (set).data[2]=0; (set).data[3]=0;
 // включает элемент n в множество set
#define Include(set,n)\
    (set).data[(n)>>3] |= (1<<((n) & 7));
// возвращает не 0, если элемент n в множестве set
#define In(set,n)\
    (  (set).data[(n)>>3]) & (1<<((n) & 7))  )

      // +++++++++++ переменные при расчёте ++++++++++++++//
 typedef struct{
 int score, ply, max;
 TMove bestMove;
 TSet set;
      } Targ, *Parg;
// максимальное значение при просчёте
#define INFINITY 30000
// максимальная глубина просчета
#define MAX_PLY 3
// проверка на конец


// ПЕЧАТЬ ПОЗИЦИИ
void writePos(int pos[10*10])
{
  int i;
  char ch;

//   printf("Hello AMELIA and ALYONA. Play the game? \n\n");

   printf("   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",-55, -51,-51, -51, -53, -51, -51, -51, -53, -51,-51, -51, -53, -51, -51, -51, -53, -51, -51, -51, -53, -51, -51, -51, -53, -51, -51, -51, -53, -51, -51, -51, -69);//нарисовали верх доски
     for (i=11; i<=88; i++){
        switch (i) {
         case 11:
             printf(" %d ",8);
             break;
         case 21:
             printf(" %d ",7);
             break;
         case 31:
             printf(" %d ",6);
             break;
         case 41:
             printf(" %d ",5);
             break;
         case 51:
             printf(" %d ",4);
             break;
         case 61:
             printf(" %d ",3);
             break;
         case 71:
             printf(" %d ",2);
             break;
         case 81:
             printf(" %d ",1);
             break;
            }

      if ((i%10) != 0 && (i%10) !=9){
         switch (i%10) {
         case 1:
             if (pos[i] == 0)  printf("%c   ",-70);
             else printf("%c %d ",-70,pos[i]);
             break;
         case 2:
             if (pos[i] == 0)  printf("%c   ",-70);
             else printf("%c %d ",-70,pos[i]);
             break;
         case 3:
             if (pos[i] == 0)  printf("%c   ",-70);
             else printf("%c %d ", -70, pos[i]);
             break;
         case 4:
             if (pos[i] == 0)  printf("%c   ",-70);
             else printf("%c %d ", -70, pos[i]);
             break;
         case 5:
             if (pos[i] == 0)  printf("%c   ",-70);
             else printf("%c %d ", -70, pos[i]);
             break;
         case 6:
             if (pos[i] == 0)  printf("%c   ",-70);
             else printf("%c %d ", -70, pos[i]);
             break;
         case 7:
             if (pos[i] == 0)  printf("%c   ",-70);
             else printf("%c %d ", -70, pos[i]);
             break;
         case 8:
             if (pos[i] == 0)  printf("%c   %c",-70,-70);
             else printf("%c %d %c", -70, pos[i], -70);
             printf("\n");
             if (i<80)
             printf("   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", -52, -51,-51, -51, -50, -51,-51, -51, -50, -51,-51, -51, -50, -51,-51, -51, -50, -51, -51, -51, -50, -51,-51, -51, -50, -51,-51, -51, -50, -51,-51, -51, -71);
             else
             printf("   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", -56, -51,-51, -51, -54, -51,-51, -51, -54, -51,-51, -51, -54, -51,-51, -51, -54, -51, -51, -51, -54, -51,-51, -51, -54, -51,-51, -51, -54, -51,-51, -51, -68);
             printf("\n");
             break;
                } //end of switch
            } //end of if ((i%10) != 0 && (i%10) !=9)
        } // end of  for (i=11; i<=88; i++)
        printf("%c  ");

        //печатаем буквы под доской ABCDEFGH
        for(i = 1; i < sizeof(alephbeth); i++)
                printf("  %c ", alephbeth[i-1]);
        printf(" \n\n");
      }


/*void printPos()
{
 int i;
    for (i=11; i<=88; i++)
      if ((i % 10) != 9 && (i % 10) != 0)
         {
            printf(" %1.1i \t",pos[i]);
            if ((i % 10) == 8) {printf("\n");}
        }
    printf("\n");
} */

int CheckEnd(void)
{
    int n;
    for (n=0; n<12; n++)
        if (pos[EndTabB[n]] != B) return 0;
    return 1;
} //function
// делает перемещение

#define MakeMove\
    pos[move.source] = 0;\
    pos[move.dest] = B;\
    pieceTabB[index] = move.dest;
// отменяет перемещение хода
#define UnMakeMove\
    pos[move.dest] = 0;\
    pos[move.source] = B;\
    pieceTabB[index] = move.source;
//+++++++FORWARS+++++++++//
void SimpleMove(Parg, int);
void Move(Parg, int);
void CallSearch(Parg,PMove);
void Search(Parg);
//простой ход на клетку
void SimpleMove(Parg arg, int index)
{
    int n;
    TMove move;
    move.source = pieceTabB[index];
    for (n = 0; n<4; n++)
    {
        move.dest = move.source + delTab[n];
        if (pos[move.dest]==0)
        {
            MakeMove;
            CallSearch(arg, &move);
            UnMakeMove
        }
    }
}// function
// прыгаем через шашку
void Move(Parg arg, int index)
{
    int n, tmp;
    TMove move;
    for (n = 0; n<4; n++)
    {
        move.source = pieceTabB[index];
        move.dest = move.source + delTab[n];
        tmp = pos[move.dest];
        if (tmp == 0 || tmp == F) continue;
        move.dest += delTab[n];
        tmp = pos[move.dest];
        if (tmp != 0) continue;
        if (In(arg->set, move.dest) continue;
        // нашли куда ходить
        Include(arg->set, move.dest);
        MakeMove
        CallSearch(arg, &move);
        Move (arg, index);
        UnMakeMove
    }//for
}//function
// вызов просчета
void CallSearch (Parg arg, PMove move)
{
    Targ nextArg;
    nextArg.ply = arg->ply+1;
    nextArg.score = arg->score + (stTab[move->dest] - stTab[move->source]);
    Search(&nextArg);
    //если нашли лучший ход
   if (nextArg.max > arg->max)
   {
       arg->max = nextArg.max;
       arg->bestMove.source = move->source;
       arg->bestMove.dest = move->dest;
   }
}// function
void Search (Parg arg)
{
    int n;
    if (arg->ply >= MAX_PLY)
    {
        arg->max = arg->score;
        return ;
    }
    if (CheckEnd())
    {
        arg->max = INFINITY - arg->ply;
        return;
    }
    arg->max = -INFINITY;
    //все перемещения на одну клетку
    for (n=0; n < 12; n++)
       SimpleMove(arg, n);
    // все перемещения через шашки
    for (n = 0; n<12; n++)
    {
        //очистим множество
        Clear(arg->set);
        //занесем стартовую координату
        Include(arg->set, pieceTabB[n]);
        Move(arg, n);
    }
}

 int corrEnter(char hod[6]){
   int i;
   int digit=0;
   TMove move;
   int tempDest=0, tempSource=0;
   char digitMove[]="12345678";
   char charMove[]="abcdefgh";

   for (i=0; i<8; i++) {  //проверяем верны ли символы ввода хода
                if (hod[0] == charMove[i]) { digit+=1; tempDest =tempDest + 1; }
                if (hod[3] == charMove[i]) { digit+=1; tempSource = tempSource + 1;}
                if (hod[1] == digitMove[i]) { digit+=1; tempDest += 90 - (digitMove[i] - '0' +10); }
                if (hod[4] == digitMove[i]) { digit+=1; tempSource += 90 - (digitMove[i] - '0' +10); }
    }
    if (digit==4) //если введенный ход символьно корректен, то проверяем на корректность начального и конечного положения
        {
                move.dest = tempDest; cout << move.dest <<endl;
                move.source= tempSource; cout << move.source <<endl;
                if ((pos[move.dest] == 1) && (pos[move.source] == 0)) return 0; else return 1;
        }

}//function

//пример первого вызова
/****************************/
int main()
{
Targ arg;
int n;
const int len = 6;
char hod[len]="";

//while (move != "exit") {
  writePos(pos);
  cout << "Enter move like this 'e2-e4'"<<endl;
  cin >> setw(len) >> hod;
  cout << "\n" <<hod<<endl;
  if (corrEnter(hod) == 0)
        {
                cout << "correct move"<<endl;

        }
                else cout << "uncorrect move";

//memset(&arg, 0, sizeof (Targ));
Search(&arg);

// изменения в позиции и в списке фигур
for (n = 0; n < 12; n++)
    if (pieceTabB[n] == arg.bestMove.source)
    {
        pieceTabB[n] = arg.bestMove.dest;
        pos[arg.bestMove.source] = 0;
        pos[arg.bestMove.dest] = B;
        break;
    }
 //printPos();
 //writePos(pos);
    return 0;
//}
}
