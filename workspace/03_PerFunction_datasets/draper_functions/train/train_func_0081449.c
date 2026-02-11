enter_buffer(buf)
    buf_T	*buf;
{

    buf_copy_options(buf, BCO_ENTER | BCO_NOHELP);
    if (!buf->b_help)
	get_winopts(buf);
#ifdef FEAT_FOLDING
    else

	clearFolding(curwin);
    foldUpdateAll(curwin);
#endif


    curwin->w_buffer = buf;
    curbuf = buf;
    ++curbuf->b_nwindows;

#ifdef FEAT_DIFF
    if (curwin->w_p_diff)
	diff_buf_add(curbuf);
#endif


    curwin->w_cursor.lnum = 1;
    curwin->w_cursor.col = 0;
#ifdef FEAT_VIRTUALEDIT
    curwin->w_cursor.coladd = 0;
#endif
    curwin->w_set_curswant = TRUE;


    if (curbuf->b_ml.ml_mfp == NULL)
    {
#ifdef FEAT_AUTOCMD


	if (*curbuf->b_p_ft == NUL)
	    did_filetype = FALSE;
#endif

	open_buffer(FALSE, NULL);
    }
    else
    {
	if (!msg_silent)
	    need_fileinfo = TRUE;
	(void)buf_check_timestamp(curbuf, FALSE);
#ifdef FEAT_AUTOCMD
	curwin->w_topline = 1;
# ifdef FEAT_DIFF
	curwin->w_topfill = 0;
# endif
	apply_autocmds(EVENT_BUFENTER, NULL, NULL, FALSE, curbuf);
	apply_autocmds(EVENT_BUFWINENTER, NULL, NULL, FALSE, curbuf);
#endif
    }


    if (curwin->w_cursor.lnum == 1 && inindent(0))
	buflist_getfpos();

    check_arg_idx(curwin);
#ifdef FEAT_TITLE
    maketitle();
#endif
#ifdef FEAT_AUTOCMD
    if (curwin->w_topline == 1)
#endif
	scroll_cursor_halfway(FALSE);

#ifdef FEAT_NETBEANS_INTG

    if (usingNetbeans && isNetbeansBuffer(curbuf))
	netbeans_file_activated(curbuf);
#endif


    DO_AUTOCHDIR

#ifdef FEAT_KEYMAP
    if (curbuf->b_kmap_state & KEYMAP_INIT)
	keymap_init();
#endif
#ifdef FEAT_SPELL


    if (!curbuf->b_help && curwin->w_p_spell && *curbuf->b_p_spl != NUL)
	did_set_spelllang(curbuf);
#endif

    redraw_later(NOT_VALID);
}
