f_remote_peek(argvars, rettv)
    typval_T	*argvars UNUSED;
    typval_T	*rettv;
{
#ifdef FEAT_CLIENTSERVER
    dictitem_T	v;
    char_u	*s = NULL;
# ifdef WIN32
    long_u	n = 0;
# endif
    char_u	*serverid;

    if (check_restricted() || check_secure())
    {
	rettv->vval.v_number = -1;
	return;
    }
    serverid = get_tv_string_chk(&argvars[0]);
    if (serverid == NULL)
    {
	rettv->vval.v_number = -1;
	return;
    }
# ifdef WIN32
    sscanf(serverid, SCANF_HEX_LONG_U, &n);
    if (n == 0)
	rettv->vval.v_number = -1;
    else
    {
	s = serverGetReply((HWND)n, FALSE, FALSE, FALSE);
	rettv->vval.v_number = (s != NULL);
    }
# elif defined(FEAT_X11)
    if (check_connection() == FAIL)
	return;

    rettv->vval.v_number = serverPeekReply(X_DISPLAY,
						serverStrToWin(serverid), &s);
# elif defined(MAC_CLIENTSERVER)
    rettv->vval.v_number = serverPeekReply(serverStrToPort(serverid), &s);
# endif

    if (argvars[1].v_type != VAR_UNKNOWN && rettv->vval.v_number > 0)
    {
	char_u		*retvar;

	v.di_tv.v_type = VAR_STRING;
	v.di_tv.vval.v_string = vim_strsave(s);
	retvar = get_tv_string_chk(&argvars[1]);
	if (retvar != NULL)
	    set_var(retvar, &v.di_tv, FALSE);
	vim_free(v.di_tv.vval.v_string);
    }
#else
    rettv->vval.v_number = -1;
#endif
}
