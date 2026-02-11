win_enter_ext(wp, undo_sync, curwin_invalid)
    win_T	*wp;
    int		undo_sync;
    int		curwin_invalid;
{
#ifdef FEAT_AUTOCMD
    int		other_buffer = FALSE;
#endif

    if (wp == curwin && !curwin_invalid)
	return;

#ifdef FEAT_AUTOCMD
    if (!curwin_invalid)
    {


	if (wp->w_buffer != curbuf)
	{
	    apply_autocmds(EVENT_BUFLEAVE, NULL, NULL, FALSE, curbuf);
	    other_buffer = TRUE;
	    if (!win_valid(wp))
		return;
	}
	apply_autocmds(EVENT_WINLEAVE, NULL, NULL, FALSE, curbuf);
	if (!win_valid(wp))
	    return;
# ifdef FEAT_EVAL

	if (aborting())
	    return;
# endif
    }
#endif


    if (undo_sync && curbuf != wp->w_buffer)
	u_sync(FALSE);

    if (wp->w_buffer != curbuf)
	buf_copy_options(wp->w_buffer, BCO_ENTER | BCO_NOHELP);
    if (!curwin_invalid)
    {
	prevwin = curwin;
	curwin->w_redr_status = TRUE;
    }
    curwin = wp;
    curbuf = wp->w_buffer;
    check_cursor();
#ifdef FEAT_VIRTUALEDIT
    if (!virtual_active())
	curwin->w_cursor.coladd = 0;
#endif
    changed_line_abv_curs();

    if (curwin->w_localdir != NULL)
    {


	if (globaldir == NULL)
	{
	    char_u	cwd[MAXPATHL];

	    if (mch_dirname(cwd, MAXPATHL) == OK)
		globaldir = vim_strsave(cwd);
	}
	if (mch_chdir((char *)curwin->w_localdir) == 0)
	    shorten_fnames(TRUE);
    }
    else if (globaldir != NULL)
    {


	ignored = mch_chdir((char *)globaldir);
	vim_free(globaldir);
	globaldir = NULL;
	shorten_fnames(TRUE);
    }

#ifdef FEAT_AUTOCMD
    apply_autocmds(EVENT_WINENTER, NULL, NULL, FALSE, curbuf);
    if (other_buffer)
	apply_autocmds(EVENT_BUFENTER, NULL, NULL, FALSE, curbuf);
#endif

#ifdef FEAT_TITLE
    maketitle();
#endif
    curwin->w_redr_status = TRUE;
    redraw_tabline = TRUE;
    if (restart_edit)
	redraw_later(VALID);


    if (curwin->w_height < p_wh && !curwin->w_p_wfh)
	win_setheight((int)p_wh);
    else if (curwin->w_height == 0)
	win_setheight(1);

#ifdef FEAT_VERTSPLIT

    if (curwin->w_width < p_wiw && !curwin->w_p_wfw)
	win_setwidth((int)p_wiw);
#endif

#ifdef FEAT_MOUSE
    setmouse();
#endif


    DO_AUTOCHDIR
}
