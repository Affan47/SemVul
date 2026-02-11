check_changed_any(hidden)
    int		hidden;
{
    int		ret = FALSE;
    buf_T	*buf;
    int		save;
    int		i;
    int		bufnum = 0;
    int		bufcount = 0;
    int		*bufnrs;
#ifdef FEAT_WINDOWS
    tabpage_T   *tp;
    win_T	*wp;
#endif

    for (buf = firstbuf; buf != NULL; buf = buf->b_next)
	++bufcount;

    if (bufcount == 0)
	return FALSE;

    bufnrs = (int *)alloc(sizeof(int) * bufcount);
    if (bufnrs == NULL)
	return FALSE;


    bufnrs[bufnum++] = curbuf->b_fnum;
#ifdef FEAT_WINDOWS

    FOR_ALL_WINDOWS(wp)
	if (wp->w_buffer != curbuf)
	    add_bufnum(bufnrs, &bufnum, wp->w_buffer->b_fnum);


    for (tp = first_tabpage; tp != NULL; tp = tp->tp_next)
	if (tp != curtab)
	    for (wp = tp->tp_firstwin; wp != NULL; wp = wp->w_next)
		add_bufnum(bufnrs, &bufnum, wp->w_buffer->b_fnum);
#endif

    for (buf = firstbuf; buf != NULL; buf = buf->b_next)
	add_bufnum(bufnrs, &bufnum, buf->b_fnum);

    for (i = 0; i < bufnum; ++i)
    {
	buf = buflist_findnr(bufnrs[i]);
	if (buf == NULL)
	    continue;
	if ((!hidden || buf->b_nwindows == 0) && bufIsChanged(buf))
	{


	    if (check_changed(buf, (p_awa ? CCGD_AW : 0)
				 | CCGD_MULTWIN
				 | CCGD_ALLBUF) && buf_valid(buf))
		break;
	}
    }

    if (i >= bufnum)
	goto theend;

    ret = TRUE;
    exiting = FALSE;
#if defined(FEAT_GUI_DIALOG) || defined(FEAT_CON_DIALOG)


    if (!(p_confirm || cmdmod.confirm))
#endif
    {


	if (vgetc_busy > 0)
	{
	    msg_row = cmdline_row;
	    msg_col = 0;
	    msg_didout = FALSE;
	}
	if (EMSG2(_("E162: No write since last change for buffer \"%s\""),
		    buf_spname(buf) != NULL ? buf_spname(buf) : buf->b_fname))
	{
	    save = no_wait_return;
	    no_wait_return = FALSE;
	    wait_return(FALSE);
	    no_wait_return = save;
	}
    }

#ifdef FEAT_WINDOWS

    if (buf != curbuf)
	FOR_ALL_TAB_WINDOWS(tp, wp)
	    if (wp->w_buffer == buf)
	    {
		goto_tabpage_win(tp, wp);
# ifdef FEAT_AUTOCMD

		if (!buf_valid(buf))
		{
		    goto theend;
		}
# endif
		goto buf_found;
	    }
buf_found:
#endif


    if (buf != curbuf)
	set_curbuf(buf, DOBUF_GOTO);

theend:
    vim_free(bufnrs);
    return ret;
}
