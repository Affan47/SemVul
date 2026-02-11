update_debug_sign(buf, lnum)
    buf_T	*buf;
    linenr_T	lnum;
{
    win_T	*wp;
    int		doit = FALSE;

# ifdef FEAT_FOLDING
    win_foldinfo.fi_level = 0;
# endif


    FOR_ALL_WINDOWS(wp)
    {
	if (buf != NULL && lnum > 0)
	{
	    if (wp->w_buffer == buf && lnum >= wp->w_topline
						      && lnum < wp->w_botline)
	    {
		if (wp->w_redraw_top == 0 || wp->w_redraw_top > lnum)
		    wp->w_redraw_top = lnum;
		if (wp->w_redraw_bot == 0 || wp->w_redraw_bot < lnum)
		    wp->w_redraw_bot = lnum;
		redraw_win_later(wp, VALID);
	    }
	}
	else
	    redraw_win_later(wp, VALID);
	if (wp->w_redr_type != 0)
	    doit = TRUE;
    }


    if (!doit || updating_screen
#ifdef FEAT_GUI
	    || gui.starting
#endif
	    || starting)
	return;


    update_prepare();

# ifdef FEAT_WINDOWS
    for (wp = firstwin; wp; wp = wp->w_next)
    {
	if (wp->w_redr_type != 0)
	    win_update(wp);
	if (wp->w_redr_status)
	    win_redr_status(wp);
    }
# else
    if (curwin->w_redr_type != 0)
	win_update(curwin);
# endif

    update_finish();
}
