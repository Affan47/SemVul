buf_spname(buf)
    buf_T	*buf;
{
#if defined(FEAT_QUICKFIX) && defined(FEAT_WINDOWS)
    if (bt_quickfix(buf))
    {
	win_T	    *win = NULL;
	tabpage_T   *tp;


	FOR_ALL_TAB_WINDOWS(tp, win)
	    if (win->w_buffer == buf)
		goto win_found;
win_found:
	if (win != NULL && win->w_llist_ref != NULL)
	    return _(msg_loclist);
	else
	    return _(msg_qflist);
    }
#endif
#ifdef FEAT_QUICKFIX


    if (bt_nofile(buf))
    {
	if (buf->b_sfname != NULL)
	    return (char *)buf->b_sfname;
	return _("[Scratch]");
    }
#endif
    if (buf->b_fname == NULL)
	return _("[No Name]");
    return NULL;
}
