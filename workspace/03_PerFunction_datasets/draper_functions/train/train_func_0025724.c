adjust_cursor()
{
	int len;

	if (curwin->w_cursor.lnum == 0)
		curwin->w_cursor.lnum = 1;
	if (curwin->w_cursor.lnum > curbuf->b_ml.ml_line_count)
		curwin->w_cursor.lnum = curbuf->b_ml.ml_line_count;

	len = STRLEN(ml_get(curwin->w_cursor.lnum));
	if (len == 0)
		curwin->w_cursor.col = 0;
	else if (curwin->w_cursor.col >= len){
		curwin->w_cursor.col = len - 1;
#ifdef KANJI
		if (ISkanjiCur() == 2 && curwin->w_cursor.col > 0)
			curwin->w_cursor.col--;
#endif
	}
}
