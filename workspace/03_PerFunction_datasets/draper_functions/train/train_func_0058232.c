PrintResult(int s)
{
        int i, j, k, cnt=0;


        for(j=2; j<=100 && j <= HistPtr; j+=2)
        {
            for(k=0; k<STATE; k++)
                if(HistoryBoards[HistPtr][k] !=
                   HistoryBoards[HistPtr-j&1023][k] )
                   {
                     goto differs;}

            if(++cnt > 1)
            {
                printf("1/2-1/2 {Draw by repetition}\n");
                return 1;
            }
          differs: ;
        }
        K=I;
        cnt = D(s,-I,I,Q,O,LL|4*S,3);
#ifdef SHATRANJ
        if(pl[s]==1 && pl[16-s]==1) {
                printf("1/2-1/2 {Insufficient mating material}\n");
                return 4;
        }
        if(pl[s]<=1 && pl[16-s]>1) {
                if (s == BLACK)
                        printf("0-1 {Bare King}\n");
                else
                        printf("1-0 {Bare King}\n");
                return 5;
        }
#else
        if(cnt>-I+1 && K==0 && L==0) {
                printf("1/2-1/2 {Stalemate}\n");
                return 2;
        }
#endif
        if(cnt==-I+1) {
                if (s == WHITE)
                        printf("0-1 {Black mates}\n");
                else
                        printf("1-0 {White mates}\n");
                return 3;
        }
        if(Fifty >=100) {
                printf("1/2-1/2 {Draw by fifty move rule}\n");
                return 4;
        }
        return 0;
}
