adjust_window(WINDOW *win, int ToLines, int ToCols, int stolen EXTRA_DCLS)
{
    int result;
    int bottom = CurLines + SP->_topstolen - stolen;
    int myLines = win->_maxy + 1;
    int myCols = win->_maxx + 1;
    ripoff_t *rop = ripped_window(win);

    T((T_CALLED("adjust_window(%p,%d,%d)%s depth %d/%d currently %ldx%ld at %ld,%ld"),
       win, ToLines, ToCols,
       (rop != 0) ? " (rip)" : "",
       parent_depth(win),
       child_depth(win),
       (long) getmaxy(win), (long) getmaxx(win),
       (long) getbegy(win) + win->_yoffset, (long) getbegx(win)));

    if (rop != 0 && rop->line < 0) {


	win->_begy = ToLines - ripped_bottom(win) - 0 - win->_yoffset;
    } else if (win->_begy >= bottom) {


	win->_begy += (ToLines - CurLines);
    } else {
	if (myLines == (CurLines - stolen)
	    && ToLines != CurLines) {
	    myLines = ToLines - stolen;
	} else if (myLines == CurLines
		   && ToLines != CurLines) {
	    myLines = ToLines;
	}
    }

    if (myLines > ToLines) {
	myLines = ToLines;
    }

    if (myCols > ToCols)
	myCols = ToCols;

    if (myCols == CurCols
	&& ToCols != CurCols)
	myCols = ToCols;

    result = wresize(win, myLines, myCols);
    returnCode(result);
}
