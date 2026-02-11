subpad(WINDOW *orig, int l, int c, int begy, int begx)
{
    WINDOW *win = (WINDOW *) 0;

    T((T_CALLED("subpad(%d, %d)"), l, c));

    if (orig) {
	if (!(orig->_flags & _ISPAD)
	    || ((win = derwin(orig, l, c, begy, begx)) == NULL))
	    returnWin(0);
    }
    returnWin(win);
}
