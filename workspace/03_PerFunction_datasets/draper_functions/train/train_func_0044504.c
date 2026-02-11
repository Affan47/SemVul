f_call(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
    char_u	*func;
    typval_T	argv[MAX_FUNC_ARGS + 1];
    int		argc = 0;
    listitem_T	*item;
    int		dummy;
    dict_T	*selfdict = NULL;

    if (argvars[1].v_type != VAR_LIST)
    {
	EMSG(_(e_listreq));
	return;
    }
    if (argvars[1].vval.v_list == NULL)
	return;

    if (argvars[0].v_type == VAR_FUNC)
	func = argvars[0].vval.v_string;
    else
	func = get_tv_string(&argvars[0]);
    if (*func == NUL)
	return;

    if (argvars[2].v_type != VAR_UNKNOWN)
    {
	if (argvars[2].v_type != VAR_DICT)
	{
	    EMSG(_(e_dictreq));
	    return;
	}
	selfdict = argvars[2].vval.v_dict;
    }

    for (item = argvars[1].vval.v_list->lv_first; item != NULL;
							 item = item->li_next)
    {
	if (argc == MAX_FUNC_ARGS)
	{
	    EMSG(_("E699: Too many arguments"));
	    break;
	}


	copy_tv(&item->li_tv, &argv[argc++]);
    }

    if (item == NULL)
	(void)call_func(func, (int)STRLEN(func), rettv, argc, argv,
				 curwin->w_cursor.lnum, curwin->w_cursor.lnum,
						      &dummy, TRUE, selfdict);


    while (argc > 0)
	clear_tv(&argv[--argc]);
}
