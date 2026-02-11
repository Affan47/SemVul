emsg(s)
    char_u	*s;
{
    int		attr;
    char_u	*p;
#ifdef FEAT_EVAL
    int		ignore = FALSE;
    int		severe;
#endif


    if (emsg_not_now())
	return TRUE;

    called_emsg = TRUE;
    ex_exitval = 1;


#ifdef FEAT_EVAL
    severe = emsg_severe;
    emsg_severe = FALSE;
#endif

    if (!emsg_off || vim_strchr(p_debug, 't') != NULL)
    {
#ifdef FEAT_EVAL


	if (cause_errthrow(s, severe, &ignore) == TRUE)
	{
	    if (!ignore)
		did_emsg = TRUE;
	    return TRUE;
	}


	set_vim_var_string(VV_ERRMSG, s, -1);
#endif


	if (emsg_silent != 0)
	{
	    msg_start();
	    p = get_emsg_source();
	    if (p != NULL)
	    {
		STRCAT(p, "\n");
		redir_write(p, -1);
		vim_free(p);
	    }
	    p = get_emsg_lnum();
	    if (p != NULL)
	    {
		STRCAT(p, "\n");
		redir_write(p, -1);
		vim_free(p);
	    }
	    redir_write(s, -1);
	    return TRUE;
	}


	msg_silent = 0;
	cmd_silent = FALSE;

	if (global_busy)
	    ++global_busy;

	if (p_eb)
	    beep_flush();
	else
	    flush_buffers(FALSE);
	did_emsg = TRUE;
    }

    emsg_on_display = TRUE;
    ++msg_scroll;
    attr = hl_attr(HLF_E);
    if (msg_scrolled != 0)
	need_wait_return = TRUE;


    msg_source(attr);


    msg_nowait = FALSE;
    return msg_attr(s, attr);
}
