buflist_getlnum()
{
	linenr_t	lnum;

	curwin->w_cursor.lnum = 1;
	curwin->w_cursor.col = 0;
	lnum = buflist_findlnum(curbuf);
	if (lnum != 0 && lnum <= curbuf->b_ml.ml_line_count)
		curwin->w_cursor.lnum = lnum;
}
