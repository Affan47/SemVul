set_curbuf(buf, action)
    buf_T	*buf;
    int		action;
{
    buf_T	*prevbuf;
    int		unload = (action == DOBUF_UNLOAD || action == DOBUF_DEL
						     || action == DOBUF_WIPE);

    setpcmark();
    if (!cmdmod.keepalt)
	curwin->w_alt_fnum = curbuf->b_fnum;
    buflist_altfpos(curwin);

#ifdef FEAT_VISUAL

    VIsual_reselect = FALSE;
#endif


    prevbuf = curbuf;

#ifdef FEAT_AUTOCMD
    apply_autocmds(EVENT_BUFLEAVE, NULL, NULL, FALSE, curbuf);
# ifdef FEAT_EVAL
    if (buf_valid(prevbuf) && !aborting())
# else
    if (buf_valid(prevbuf))
# endif
#endif
    {
#ifdef FEAT_WINDOWS
	if (unload)
	    close_windows(prevbuf, FALSE);
#endif
#if defined(FEAT_AUTOCMD) && defined(FEAT_EVAL)
	if (buf_valid(prevbuf) && !aborting())
#else
	if (buf_valid(prevbuf))
#endif
	{
	    if (prevbuf == curbuf)
		u_sync(FALSE);
	    close_buffer(prevbuf == curwin->w_buffer ? curwin : NULL, prevbuf,
		    unload ? action : (action == DOBUF_GOTO
			&& !P_HID(prevbuf)
			&& !bufIsChanged(prevbuf)) ? DOBUF_UNLOAD : 0);
	}
    }
#ifdef FEAT_AUTOCMD


# ifdef FEAT_EVAL
    if (buf_valid(buf) && buf != curbuf && !aborting())
# else
    if (buf_valid(buf) && buf != curbuf)
# endif
#endif
	enter_buffer(buf);
}
