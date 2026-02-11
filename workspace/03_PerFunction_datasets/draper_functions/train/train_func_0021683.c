win_free(wp, tp)
    win_T	*wp;
    tabpage_T	*tp;
{
    int		i;
    buf_T	*buf;
    wininfo_T	*wip;

#ifdef FEAT_FOLDING
    clearFolding(wp);
#endif


    alist_unlink(wp->w_alist);

#ifdef FEAT_AUTOCMD


    block_autocmds();
#endif

#ifdef FEAT_LUA
    lua_window_free(wp);
#endif

#ifdef FEAT_MZSCHEME
    mzscheme_window_free(wp);
#endif

#ifdef FEAT_PERL
    perl_win_free(wp);
#endif

#ifdef FEAT_PYTHON
    python_window_free(wp);
#endif

#ifdef FEAT_PYTHON3
    python3_window_free(wp);
#endif

#ifdef FEAT_TCL
    tcl_window_free(wp);
#endif

#ifdef FEAT_RUBY
    ruby_window_free(wp);
#endif

    clear_winopt(&wp->w_onebuf_opt);
    clear_winopt(&wp->w_allbuf_opt);

#ifdef FEAT_EVAL
    vars_clear(&wp->w_vars->dv_hashtab);
    hash_init(&wp->w_vars->dv_hashtab);
    unref_var_dict(wp->w_vars);
#endif

    if (prevwin == wp)
	prevwin = NULL;
    win_free_lsize(wp);

    for (i = 0; i < wp->w_tagstacklen; ++i)
	vim_free(wp->w_tagstack[i].tagname);

    vim_free(wp->w_localdir);


    for (buf = firstbuf; buf != NULL; buf = buf->b_next)
	for (wip = buf->b_wininfo; wip != NULL; wip = wip->wi_next)
	    if (wip->wi_win == wp)
		wip->wi_win = NULL;

#ifdef FEAT_SEARCH_EXTRA
    clear_matches(wp);
#endif

#ifdef FEAT_JUMPLIST
    free_jumplist(wp);
#endif

#ifdef FEAT_QUICKFIX
    qf_free_all(wp);
#endif

#ifdef FEAT_GUI
    if (gui.in_use)
    {
	gui_mch_destroy_scrollbar(&wp->w_scrollbars[SBAR_LEFT]);
	gui_mch_destroy_scrollbar(&wp->w_scrollbars[SBAR_RIGHT]);
    }
#endif

#ifdef FEAT_SYN_HL
    vim_free(wp->w_p_cc_cols);
#endif

#ifdef FEAT_AUTOCMD
    if (wp != aucmd_win)
#endif
	win_remove(wp, tp);
    vim_free(wp);

#ifdef FEAT_AUTOCMD
    unblock_autocmds();
#endif
}
