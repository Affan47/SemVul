throw_exception(value, type, cmdname)
    void	*value;
    int		type;
    char_u	*cmdname;
{
    except_T	*excp;
    int		should_free;


    if (type == ET_USER)
    {
	if (STRNCMP((char_u *)value, "Vim", 3) == 0
		&& (((char_u *)value)[3] == NUL || ((char_u *)value)[3] == ':'
		    || ((char_u *)value)[3] == '('))
	{
	    EMSG(_("E608: Cannot :throw exceptions with 'Vim' prefix"));
	    goto fail;
	}
    }

    excp = (except_T *)alloc((unsigned)sizeof(except_T));
    if (excp == NULL)
	goto nomem;

    if (type == ET_ERROR)


	excp->messages = (struct msglist *)value;

    excp->value = get_exception_string(value, type, cmdname, &should_free);
    if (excp->value == NULL && should_free)
	goto nomem;

    excp->type = type;
    excp->throw_name = vim_strsave(sourcing_name == NULL
					      ? (char_u *)"" : sourcing_name);
    if (excp->throw_name == NULL)
    {
	if (should_free)
	    vim_free(excp->value);
	goto nomem;
    }
    excp->throw_lnum = sourcing_lnum;

    if (p_verbose >= 13 || debug_break_level > 0)
    {
	int	save_msg_silent = msg_silent;

	if (debug_break_level > 0)
	    msg_silent = FALSE;
	else
	    verbose_enter();
	++no_wait_return;
	if (debug_break_level > 0 || *p_vfile == NUL)
	    msg_scroll = TRUE;

	smsg((char_u *)_("Exception thrown: %s"), excp->value);
	msg_puts((char_u *)"\n");

	if (debug_break_level > 0 || *p_vfile == NUL)
	    cmdline_row = msg_row;
	--no_wait_return;
	if (debug_break_level > 0)
	    msg_silent = save_msg_silent;
	else
	    verbose_leave();
    }

    current_exception = excp;
    return OK;

nomem:
    vim_free(excp);
    suppress_errthrow = TRUE;
    EMSG(_(e_outofmem));
fail:
    current_exception = NULL;
    return FAIL;
}
