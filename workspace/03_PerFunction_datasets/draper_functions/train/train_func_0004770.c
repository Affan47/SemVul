get_user_input(argvars, rettv, inputdialog)
    typval_T	*argvars;
    typval_T	*rettv;
    int		inputdialog;
{
    char_u	*prompt = get_tv_string_chk(&argvars[0]);
    char_u	*p = NULL;
    int		c;
    char_u	buf[NUMBUFLEN];
    int		cmd_silent_save = cmd_silent;
    char_u	*defstr = (char_u *)"";
    int		xp_type = EXPAND_NOTHING;
    char_u	*xp_arg = NULL;

    rettv->v_type = VAR_STRING;
    rettv->vval.v_string = NULL;

#ifdef NO_CONSOLE_INPUT

    if (no_console_input())
	return;
#endif

    cmd_silent = FALSE;
    if (prompt != NULL)
    {


	p = vim_strrchr(prompt, '\n');
	if (p == NULL)
	    p = prompt;
	else
	{
	    ++p;
	    c = *p;
	    *p = NUL;
	    msg_start();
	    msg_clr_eos();
	    msg_puts_attr(prompt, echo_attr);
	    msg_didout = FALSE;
	    msg_starthere();
	    *p = c;
	}
	cmdline_row = msg_row;

	if (argvars[1].v_type != VAR_UNKNOWN)
	{
	    defstr = get_tv_string_buf_chk(&argvars[1], buf);
	    if (defstr != NULL)
		stuffReadbuffSpec(defstr);

	    if (!inputdialog && argvars[2].v_type != VAR_UNKNOWN)
	    {
		char_u	*xp_name;
		int	xp_namelen;
		long	argt;


		rettv->vval.v_string = NULL;

		xp_name = get_tv_string_buf_chk(&argvars[2], buf);
		if (xp_name == NULL)
		    return;

		xp_namelen = (int)STRLEN(xp_name);

		if (parse_compl_arg(xp_name, xp_namelen, &xp_type, &argt,
							     &xp_arg) == FAIL)
		    return;
	    }
	}

	if (defstr != NULL)
	    rettv->vval.v_string =
		getcmdline_prompt(inputsecret_flag ? NUL : '@', p, echo_attr,
				  xp_type, xp_arg);
	if (inputdialog && rettv->vval.v_string == NULL
		&& argvars[1].v_type != VAR_UNKNOWN
		&& argvars[2].v_type != VAR_UNKNOWN)
	    rettv->vval.v_string = vim_strsave(get_tv_string_buf(
							   &argvars[2], buf));

	vim_free(xp_arg);


	need_wait_return = FALSE;
	msg_didout = FALSE;
    }
    cmd_silent = cmd_silent_save;
}
