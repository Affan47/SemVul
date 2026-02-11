win_close_othertab(win, free_buf, tp)
    win_T	*win;
    int		free_buf;
    tabpage_T	*tp;
{
    win_T	*wp;
    int		dir;
    tabpage_T   *ptp = NULL;
    int		free_tp = FALSE;

#ifdef FEAT_AUTOCMD
    if (win->w_closing || win->w_buffer->b_closing)
	return;
#endif


    close_buffer(win, win->w_buffer, free_buf ? DOBUF_UNLOAD : 0, FALSE);


    for (ptp = first_tabpage; ptp != NULL && ptp != tp; ptp = ptp->tp_next)
	;
    if (ptp == NULL || tp == curtab)
	return;


    for (wp = tp->tp_firstwin; wp != NULL && wp != win; wp = wp->w_next)
	;
    if (wp == NULL)
	return;


    if (tp == NULL ? firstwin == lastwin : tp->tp_firstwin == tp->tp_lastwin)
    {
	if (tp == first_tabpage)
	    first_tabpage = tp->tp_next;
	else
	{
	    for (ptp = first_tabpage; ptp != NULL && ptp->tp_next != tp;
							   ptp = ptp->tp_next)
		;
	    if (ptp == NULL)
	    {
		EMSG2(_(e_intern2), "win_close_othertab()");
		return;
	    }
	    ptp->tp_next = tp->tp_next;
	}
	free_tp = TRUE;
    }


    win_free_mem(win, &dir, tp);

    if (free_tp)
	free_tabpage(tp);
}
