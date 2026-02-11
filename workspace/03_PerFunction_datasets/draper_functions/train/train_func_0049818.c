go1(int from, int field)
{
    from=internal(from);
    field=internal(field);

    to=field;

    if(checkCapture1()) {
        bool capture=false;

        switch(board[from]) {
        case MAN1:
            if(manCapture1(from, UL, capture)) return true;
            if(manCapture1(from, UR, capture)) return true;
            return false;
        case KING1:
            if(kingCapture1(from, UL, capture)) return true;
            if(kingCapture1(from, UR, capture)) return true;
            if(kingCapture1(from, DL, capture)) return true;
            if(kingCapture1(from, DR, capture)) return true;
            return false;
        }

    } else {
        switch(board[from]) {
        case MAN1:
            if((to==(from-6))||(to==(from-5))) {
                board[from]=FREE;
                if(to<10)
		    board[to]=KING1;
                else
		    board[to]=MAN1;
                return true;
            }
            return false;
        case KING1:
	    if((to==(from-6))||(to==(from-5)) ||
		    (to==(from+5))||(to==(from+6)) ) {
		board[from]=FREE;
                board[to]=KING1;
                return true;
            }
            return false;
        }
    }

    return false;
}
