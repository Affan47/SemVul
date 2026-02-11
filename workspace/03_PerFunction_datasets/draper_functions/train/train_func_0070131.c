f_remove(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
    list_T	*l;
    listitem_T	*item, *item2;
    listitem_T	*li;
    long	idx;
    long	end;
    char_u	*key;
    dict_T	*d;
    dictitem_T	*di;

    rettv->vval.v_number = 0;
    if (argvars[0].v_type == VAR_DICT)
    {
	if (argvars[2].v_type != VAR_UNKNOWN)
	    EMSG2(_(e_toomanyarg), "remove()");
	else if ((d = argvars[0].vval.v_dict) != NULL
		&& !tv_check_lock(d->dv_lock, (char_u *)"remove() argument"))
	{
	    key = get_tv_string_chk(&argvars[1]);
	    if (key != NULL)
	    {
		di = dict_find(d, key, -1);
		if (di == NULL)
		    EMSG2(_(e_dictkey), key);
		else
		{
		    *rettv = di->di_tv;
		    init_tv(&di->di_tv);
		    dictitem_remove(d, di);
		}
	    }
	}
    }
    else if (argvars[0].v_type != VAR_LIST)
	EMSG2(_(e_listdictarg), "remove()");
    else if ((l = argvars[0].vval.v_list) != NULL
	    && !tv_check_lock(l->lv_lock, (char_u *)"remove() argument"))
    {
	int	    error = FALSE;

	idx = get_tv_number_chk(&argvars[1], &error);
	if (error)
	    ;
	else if ((item = list_find(l, idx)) == NULL)
	    EMSGN(_(e_listidx), idx);
	else
	{
	    if (argvars[2].v_type == VAR_UNKNOWN)
	    {

		list_remove(l, item, item);
		*rettv = item->li_tv;
		vim_free(item);
	    }
	    else
	    {

		end = get_tv_number_chk(&argvars[2], &error);
		if (error)
		    ;
		else if ((item2 = list_find(l, end)) == NULL)
		    EMSGN(_(e_listidx), end);
		else
		{
		    int	    cnt = 0;

		    for (li = item; li != NULL; li = li->li_next)
		    {
			++cnt;
			if (li == item2)
			    break;
		    }
		    if (li == NULL)
			EMSG(_(e_invrange));
		    else
		    {
			list_remove(l, item, item2);
			if (rettv_list_alloc(rettv) == OK)
			{
			    l = rettv->vval.v_list;
			    l->lv_first = item;
			    l->lv_last = item2;
			    item->li_prev = NULL;
			    item2->li_next = NULL;
			    l->lv_len = cnt;
			}
		    }
		}
	    }
	}
    }
}
