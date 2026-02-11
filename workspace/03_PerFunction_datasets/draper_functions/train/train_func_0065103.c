win_do_lines(wp, row, line_count, mayclear, del)
    win_T	*wp;
    int		row;
    int		line_count;
    int		mayclear;
    int		del;
{
    int		retval;

    if (!redrawing() || line_count <= 0)
	return FAIL;


    if (mayclear && Rows - line_count < 5
#ifdef FEAT_VERTSPLIT
	    && wp->w_width == Columns
#endif
	    )
    {
	screenclear();
	return FAIL;
    }


    if (row + line_count >= wp->w_height)
    {
	screen_fill(W_WINROW(wp) + row, W_WINROW(wp) + wp->w_height,
		W_WINCOL(wp), (int)W_ENDCOL(wp),
		' ', ' ', 0);
	return OK;
    }


    clear_cmdline = TRUE;


    if (scroll_region
#ifdef FEAT_VERTSPLIT
	    || W_WIDTH(wp) != Columns
#endif
	    )
    {
#ifdef FEAT_VERTSPLIT
	if (scroll_region && (wp->w_width == Columns || *T_CSV != NUL))
#endif
	    scroll_region_set(wp, row);
	if (del)
	    retval = screen_del_lines(W_WINROW(wp) + row, 0, line_count,
					       wp->w_height - row, FALSE, wp);
	else
	    retval = screen_ins_lines(W_WINROW(wp) + row, 0, line_count,
						      wp->w_height - row, wp);
#ifdef FEAT_VERTSPLIT
	if (scroll_region && (wp->w_width == Columns || *T_CSV != NUL))
#endif
	    scroll_region_reset();
	return retval;
    }

#ifdef FEAT_WINDOWS
    if (wp->w_next != NULL && p_tf)
	return FAIL;
#endif

    return MAYBE;
}
