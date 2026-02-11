gui_do_horiz_scroll(leftcol, compute_longest_lnum)
    long_u	leftcol;
    int		compute_longest_lnum;
{

    if (curwin->w_p_wrap)
	return FALSE;

    if (curwin->w_leftcol == (colnr_T)leftcol)
	return FALSE;

    curwin->w_leftcol = (colnr_T)leftcol;


    if (vim_strchr(p_go, GO_HORSCROLL) == NULL
	    && !virtual_active()
	    && (colnr_T)leftcol > scroll_line_len(curwin->w_cursor.lnum))
    {
	if (compute_longest_lnum)
	{
	    curwin->w_cursor.lnum = gui_find_longest_lnum();
	    curwin->w_cursor.col = 0;
	}

	else if (longest_lnum >= curwin->w_topline
		&& longest_lnum < curwin->w_botline)
	{
	    curwin->w_cursor.lnum = longest_lnum;
	    curwin->w_cursor.col = 0;
	}
    }

    return leftcol_changed();
}
