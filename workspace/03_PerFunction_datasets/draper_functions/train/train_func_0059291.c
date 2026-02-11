checkCapture2() const
{
    for(int i=6;i<48;i++)
    {
        switch(board[i])
        {
        case MAN2:
            if(board[i+5]==MAN1 || board[i+5]==KING1)
                if(board[i+10]==FREE) return true;
            if(board[i+6]==MAN1 || board[i+6]==KING1)
                if(board[i+12]==FREE) return true;
            break;
        case KING2:
            if(board[i-6]==MAN1 || board[i-6]==KING1)
                if(board[i-12]==FREE) return true;
            if(board[i-5]==MAN1 || board[i-5]==KING1)
                if(board[i-10]==FREE) return true;
            if(board[i+5]==MAN1 || board[i+5]==KING1)
                if(board[i+10]==FREE) return true;
            if(board[i+6]==MAN1 || board[i+6]==KING1)
                if(board[i+12]==FREE) return true;
        }
    }
    return false;
}
