f_extend(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
    char      *arg_errmsg = N_("extend() argument");

    if (argvars[0].v_type == VAR_LIST && argvars[1].v_type == VAR_LIST)
    {
	list_T		*l1, *l2;
	listitem_T	*item;
	long		before;
	int		error = FALSE;

	l1 = argvars[0].vval.v_list;
	l2 = argvars[1].vval.v_list;
	if (l1 != NULL && !tv_check_lock(l1->lv_lock, (char_u *)_(arg_errmsg))
		&& l2 != NULL)
	{
	    if (argvars[2].v_type != VAR_UNKNOWN)
	    {
		before = get_tv_number_chk(&argvars[2], &error);
		if (error)
		    return;

		if (before == l1->lv_len)
		    item = NULL;
		else
		{
		    item = list_find(l1, before);
		    if (item == NULL)
		    {
			EMSGN(_(e_listidx), before);
			return;
		    }
		}
	    }
	    else
		item = NULL;
	    list_extend(l1, l2, item);

	    copy_tv(&argvars[0], rettv);
	}
    }
    else if (argvars[0].v_type == VAR_DICT && argvars[1].v_type == VAR_DICT)
    {
	dict_T	*d1, *d2;
	char_u	*action;
	int	i;

	d1 = argvars[0].vval.v_dict;
	d2 = argvars[1].vval.v_dict;
	if (d1 != NULL && !tv_check_lock(d1->dv_lock, (char_u *)_(arg_errmsg))
		&& d2 != NULL)
	{

	    if (argvars[2].v_type != VAR_UNKNOWN)
	    {
		static char *(av[]) = {"keep", "force", "error"};

		action = get_tv_string_chk(&argvars[2]);
		if (action == NULL)
		    return;
		for (i = 0; i < 3; ++i)
		    if (STRCMP(action, av[i]) == 0)
			break;
		if (i == 3)
		{
		    EMSG2(_(e_invarg2), action);
		    return;
		}
	    }
	    else
		action = (char_u *)"force";

	    dict_extend(d1, d2, action);

	    copy_tv(&argvars[0], rettv);
	}
    }
    else
	EMSG2(_(e_listdictarg), "extend()");
}
