checkCapture1(int i) const
{
    switch(board[i])
    {
    case MAN1:
	if(board[i-6]==MAN2 || board[i-6]==KING2)
	    if(board[i-12]==FREE) return true;
	if(board[i-5]==MAN2 || board[i-5]==KING2)
	    if(board[i-10]==FREE) return true;
	if(board[i+5]==MAN2 || board[i+5]==KING2)
	    if(board[i+10]==FREE) return true;
	if(board[i+6]==MAN2 || board[i+6]==KING2)
	    if(board[i+12]==FREE) return true;
	break;
    case KING1:
	int k;
	for(k=i-6;board[k]==FREE;k-=6);
	if(board[k]==MAN2 || board[k]==KING2)
	    if(board[k-6]==FREE) return true;

	for(k=i-5;board[k]==FREE;k-=5);
	if(board[k]==MAN2 || board[k]==KING2)
	    if(board[k-5]==FREE) return true;

	for(k=i+5;board[k]==FREE;k+=5);
	if(board[k]==MAN2 || board[k]==KING2)
	    if(board[k+5]==FREE) return true;

	for(k=i+6;board[k]==FREE;k+=6);
	if(board[k]==MAN2 || board[k]==KING2)
	    if(board[k+6]==FREE) return true;
    }

    return false;
}
