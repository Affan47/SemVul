gui_do_scroll()
{
    win_T	*wp, *save_wp;
    int		i;
    long	nlines;
    pos_T	old_cursor;
    linenr_T	old_topline;
#ifdef FEAT_DIFF
    int		old_topfill;
#endif

    for (wp = firstwin, i = 0; i < current_scrollbar; wp = W_NEXT(wp), i++)
	if (wp == NULL)
	    break;
    if (wp == NULL)

	return FALSE;


    nlines = (long)scrollbar_value + 1 - (long)wp->w_topline;
    if (nlines == 0)
	return FALSE;

    save_wp = curwin;
    old_topline = wp->w_topline;
#ifdef FEAT_DIFF
    old_topfill = wp->w_topfill;
#endif
    old_cursor = wp->w_cursor;
    curwin = wp;
    curbuf = wp->w_buffer;
    if (nlines < 0)
	scrolldown(-nlines, gui.dragged_wp == NULL);
    else
	scrollup(nlines, gui.dragged_wp == NULL);


    if (gui.dragged_sb == SBAR_NONE)
	gui.dragged_wp = NULL;

    if (old_topline != wp->w_topline
#ifdef FEAT_DIFF
	    || old_topfill != wp->w_topfill
#endif
	    )
    {
	if (p_so != 0)
	{
	    cursor_correct();
	    update_topline();
	}
	if (old_cursor.lnum != wp->w_cursor.lnum)
	    coladvance(wp->w_curswant);
#ifdef FEAT_SCROLLBIND
	wp->w_scbind_pos = wp->w_topline;
#endif
    }


    validate_cursor();

    curwin = save_wp;
    curbuf = save_wp->w_buffer;


    if (old_topline != wp->w_topline
	    || wp->w_redr_type != 0
#ifdef FEAT_DIFF
	    || old_topfill != wp->w_topfill
#endif
	    )
    {
	int type = VALID;

#ifdef FEAT_INS_EXPAND
	if (pum_visible())
	{
	    type = NOT_VALID;
	    wp->w_lines_valid = 0;
	}
#endif


	if (wp->w_redr_type < type)
	    wp->w_redr_type = type;
	updateWindow(wp);
    }

#ifdef FEAT_INS_EXPAND

    if (pum_visible())
	pum_redraw();
#endif

    return (wp == curwin && !equalpos(curwin->w_cursor, old_cursor));
}
