getwinvar(argvars, rettv, off)
    typval_T	*argvars;
    typval_T	*rettv;
    int		off;
{
    win_T	*win, *oldcurwin;
    char_u	*varname;
    dictitem_T	*v;
    tabpage_T	*tp;

#ifdef FEAT_WINDOWS
    if (off == 1)
	tp = find_tabpage((int)get_tv_number_chk(&argvars[0], NULL));
    else
	tp = curtab;
#endif
    win = find_win_by_nr(&argvars[off], tp);
    varname = get_tv_string_chk(&argvars[off + 1]);
    ++emsg_off;

    rettv->v_type = VAR_STRING;
    rettv->vval.v_string = NULL;

    if (win != NULL && varname != NULL)
    {


	oldcurwin = curwin;
	curwin = win;
	curbuf = win->w_buffer;

	if (*varname == '&')
	    get_option_tv(&varname, rettv, 1);
	else
	{
	    if (*varname == NUL)


		varname = (char_u *)"w:" + 2;

	    v = find_var_in_ht(&win->w_vars.dv_hashtab, varname, FALSE);
	    if (v != NULL)
		copy_tv(&v->di_tv, rettv);
	}


	curwin = oldcurwin;
	curbuf = curwin->w_buffer;
    }

    --emsg_off;
}
