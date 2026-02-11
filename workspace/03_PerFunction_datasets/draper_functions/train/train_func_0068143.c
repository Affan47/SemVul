reg_match_visual()
{
    pos_T	top, bot;
    linenr_T    lnum;
    colnr_T	col;
    win_T	*wp = reg_win == NULL ? curwin : reg_win;
    int		mode;
    colnr_T	start, end;
    colnr_T	start2, end2;
    colnr_T	cols;


    if (reg_buf != curbuf || VIsual.lnum == 0)
	return FALSE;

    if (VIsual_active)
    {
	if (lt(VIsual, wp->w_cursor))
	{
	    top = VIsual;
	    bot = wp->w_cursor;
	}
	else
	{
	    top = wp->w_cursor;
	    bot = VIsual;
	}
	mode = VIsual_mode;
    }
    else
    {
	if (lt(curbuf->b_visual.vi_start, curbuf->b_visual.vi_end))
	{
	    top = curbuf->b_visual.vi_start;
	    bot = curbuf->b_visual.vi_end;
	}
	else
	{
	    top = curbuf->b_visual.vi_end;
	    bot = curbuf->b_visual.vi_start;
	}
	mode = curbuf->b_visual.vi_mode;
    }
    lnum = reglnum + reg_firstlnum;
    if (lnum < top.lnum || lnum > bot.lnum)
	return FALSE;

    if (mode == 'v')
    {
	col = (colnr_T)(reginput - regline);
	if ((lnum == top.lnum && col < top.col)
		|| (lnum == bot.lnum && col >= bot.col + (*p_sel != 'e')))
	    return FALSE;
    }
    else if (mode == Ctrl_V)
    {
	getvvcol(wp, &top, &start, NULL, &end);
	getvvcol(wp, &bot, &start2, NULL, &end2);
	if (start2 < start)
	    start = start2;
	if (end2 > end)
	    end = end2;
	if (top.col == MAXCOL || bot.col == MAXCOL)
	    end = MAXCOL;
	cols = win_linetabsize(wp, regline, (colnr_T)(reginput - regline));
	if (cols < start || cols > end - (*p_sel == 'e'))
	    return FALSE;
    }
    return TRUE;
}
