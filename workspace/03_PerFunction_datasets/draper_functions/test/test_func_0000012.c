kingCapture1(int from,int direction,bool &capture)
{
    int i;
    for(i=from+direction;board[i]==FREE;i+=direction);

    if(board[i]==MAN2 || board[i]==KING2)
    {
        int k=i+direction;
        if(board[k]==FREE)
        {
            bool next=false;
            int save=board[i];
            board[from]=FREE;
            board[i]=NONE;

            for(;board[k]==FREE;k+=direction)
            {
                board[k]=KING1;
                if(direction==UL || direction==DR)
                {
                    if(kingCapture1(k,UR,next)) {board[i]=FREE;return true;}
                    if(kingCapture1(k,DL,next)) {board[i]=FREE;return true;}
                }
                else
                {
                    if(kingCapture1(k,UL,next)) {board[i]=FREE;return true;}
                    if(kingCapture1(k,DR,next)) {board[i]=FREE;return true;}
                }
                board[k]=FREE;
            }

            board[k-=direction]=KING1;
            if(kingCapture1(k,direction,next)) {board[i]=FREE;return true;}
            board[k]=FREE;

            if(!next)
                for(;k!=i;k-=direction)
                    if(k==to) {board[i]=FREE;board[k]=KING1;return true;}

            board[i]=save;
            board[from]=KING1;
            capture=true;
        }
    }
    return false;
}
