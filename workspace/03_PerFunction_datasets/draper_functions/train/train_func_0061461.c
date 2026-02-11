getout(exitval)
    int		exitval;
{
#ifdef FEAT_AUTOCMD
    buf_T	*buf;
    win_T	*wp;
    tabpage_T	*tp, *next_tp;
#endif

    exiting = TRUE;


    if (exmode_active)
	exitval += ex_exitval;


#ifdef FEAT_GUI
    if (!gui.in_use)
#endif
	windgoto((int)Rows - 1, 0);

#if defined(FEAT_EVAL) || defined(FEAT_SYN_HL)

    hash_debug_results();
#endif

#ifdef FEAT_GUI
    msg_didany = FALSE;
#endif

#ifdef FEAT_AUTOCMD
    if (get_vim_var_nr(VV_DYING) <= 1)
    {

# if defined FEAT_WINDOWS
	for (tp = first_tabpage; tp != NULL; tp = next_tp)
	{
	    next_tp = tp->tp_next;
	    for (wp = (tp == curtab)
		    ? firstwin : tp->tp_firstwin; wp != NULL; wp = wp->w_next)
	    {
		buf = wp->w_buffer;
		if (buf->b_changedtick != -1)
		{
		    apply_autocmds(EVENT_BUFWINLEAVE, buf->b_fname,
						    buf->b_fname, FALSE, buf);
		    buf->b_changedtick = -1;

		    next_tp = first_tabpage;
		    break;
		}
	    }
	}
# else
	apply_autocmds(EVENT_BUFWINLEAVE, curbuf, curbuf->b_fname,
							       FALSE, curbuf);
# endif


	for (buf = firstbuf; buf != NULL; buf = buf->b_next)
	    if (buf->b_ml.ml_mfp != NULL)
	    {
		apply_autocmds(EVENT_BUFUNLOAD, buf->b_fname, buf->b_fname,
								  FALSE, buf);
		if (!buf_valid(buf))
		    break;
	    }
	apply_autocmds(EVENT_VIMLEAVEPRE, NULL, NULL, FALSE, curbuf);
    }
#endif

#ifdef FEAT_VIMINFO
    if (*p_viminfo != NUL)

	write_viminfo(NULL, FALSE);
#endif

#ifdef FEAT_AUTOCMD
    if (get_vim_var_nr(VV_DYING) <= 1)
	apply_autocmds(EVENT_VIMLEAVE, NULL, NULL, FALSE, curbuf);
#endif

#ifdef FEAT_PROFILE
    profile_dump();
#endif

    if (did_emsg
#ifdef FEAT_GUI
	    || (gui.in_use && msg_didany && p_verbose > 0)
#endif
	    )
    {

	no_wait_return = FALSE;
	wait_return(FALSE);
    }

#ifdef FEAT_AUTOCMD

# ifdef FEAT_GUI
    if (!gui.in_use)
# endif
	windgoto((int)Rows - 1, 0);
#endif

#ifdef FEAT_LUA
    lua_end();
#endif
#ifdef FEAT_MZSCHEME
    mzscheme_end();
#endif
#ifdef FEAT_TCL
    tcl_end();
#endif
#ifdef FEAT_RUBY
    ruby_end();
#endif
#ifdef FEAT_PYTHON
    python_end();
#endif
#ifdef FEAT_PYTHON3
    python3_end();
#endif
#ifdef FEAT_PERL
    perl_end();
#endif
#if defined(USE_ICONV) && defined(DYNAMIC_ICONV)
    iconv_end();
#endif
#ifdef FEAT_NETBEANS_INTG
    netbeans_end();
#endif
#ifdef FEAT_CSCOPE
    cs_end();
#endif
#ifdef FEAT_EVAL
    if (garbage_collect_at_exit)
	garbage_collect();
#endif

    mch_exit(exitval);
}
