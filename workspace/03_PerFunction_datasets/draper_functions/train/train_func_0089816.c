set_qf_ll_list(wp, list_arg, action_arg, rettv)
    win_T	*wp;
    typval_T	*list_arg;
    typval_T	*action_arg;
    typval_T	*rettv;
{
#ifdef FEAT_QUICKFIX
    char_u	*act;
    int		action = ' ';
#endif

    rettv->vval.v_number = -1;

#ifdef FEAT_QUICKFIX
    if (list_arg->v_type != VAR_LIST)
	EMSG(_(e_listreq));
    else
    {
	list_T  *l = list_arg->vval.v_list;

	if (action_arg->v_type == VAR_STRING)
	{
	    act = get_tv_string_chk(action_arg);
	    if (act == NULL)
		return;
	    if (*act == 'a' || *act == 'r')
		action = *act;
	}

	if (l != NULL && set_errorlist(wp, l, action) == OK)
	    rettv->vval.v_number = 0;
    }
#endif
}
