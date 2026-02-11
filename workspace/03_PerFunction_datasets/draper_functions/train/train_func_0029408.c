getvvcol(wp, pos, start, cursor, end)
    win_T	*wp;
    pos_T	*pos;
    colnr_T	*start;
    colnr_T	*cursor;
    colnr_T	*end;
{
    colnr_T	col;
    colnr_T	coladd;
    colnr_T	endadd;
# ifdef FEAT_MBYTE
    char_u	*ptr;
# endif

    if (virtual_active())
    {

	getvcol(wp, pos, &col, NULL, NULL);

	coladd = pos->coladd;
	endadd = 0;
# ifdef FEAT_MBYTE

	ptr = ml_get_buf(wp->w_buffer, pos->lnum, FALSE);
	if (pos->col < (colnr_T)STRLEN(ptr))
	{
	    int c = (*mb_ptr2char)(ptr + pos->col);

	    if (c != TAB && vim_isprintc(c))
	    {
		endadd = (colnr_T)(char2cells(c) - 1);
		if (coladd > endadd)
		    endadd = 0;
		else
		    coladd = 0;
	    }
	}
# endif
	col += coladd;
	if (start != NULL)
	    *start = col;
	if (cursor != NULL)
	    *cursor = col;
	if (end != NULL)
	    *end = col + endadd;
    }
    else
	getvcol(wp, pos, start, cursor, end);
}
