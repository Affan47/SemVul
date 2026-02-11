f_exists(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
    char_u	*p;
    char_u	*name;
    int		n = FALSE;
    int		len = 0;

    no_autoload = TRUE;

    p = get_tv_string(&argvars[0]);
    if (*p == '$')
    {

	if (mch_getenv(p + 1) != NULL)
	    n = TRUE;
	else
	{

	    p = expand_env_save(p);
	    if (p != NULL && *p != '$')
		n = TRUE;
	    vim_free(p);
	}
    }
    else if (*p == '&' || *p == '+')
    {
	n = (get_option_tv(&p, NULL, TRUE) == OK);
	if (*skipwhite(p) != NUL)
	    n = FALSE;
    }
    else if (*p == '*')
    {
	n = function_exists(p + 1);
    }
    else if (*p == ':')
    {
	n = cmd_exists(p + 1);
    }
    else if (*p == '#')
    {
#ifdef FEAT_AUTOCMD
	if (p[1] == '#')
	    n = autocmd_supported(p + 2);
	else
	    n = au_exists(p + 1);
#endif
    }
    else
    {
	char_u	    *tofree;
	typval_T    tv;


	name = p;
	len = get_name_len(&p, &tofree, TRUE, FALSE);
	if (len > 0)
	{
	    if (tofree != NULL)
		name = tofree;
	    n = (get_var_tv(name, len, &tv, FALSE) == OK);
	    if (n)
	    {

		n = (handle_subscript(&p, &tv, TRUE, FALSE) == OK);
		if (n)
		    clear_tv(&tv);
	    }
	}
	if (*p != NUL)
	    n = FALSE;

	vim_free(tofree);
    }

    rettv->vval.v_number = n;

    no_autoload = FALSE;
}
