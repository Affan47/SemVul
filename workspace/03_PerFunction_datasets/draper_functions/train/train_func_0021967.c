f_getbufvar(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
    buf_T	*buf;
    buf_T	*save_curbuf;
    char_u	*varname;
    dictitem_T	*v;
    int		done = FALSE;

    (void)get_tv_number(&argvars[0]);
    varname = get_tv_string_chk(&argvars[1]);
    ++emsg_off;
    buf = get_buf_tv(&argvars[0], FALSE);

    rettv->v_type = VAR_STRING;
    rettv->vval.v_string = NULL;

    if (buf != NULL && varname != NULL)
    {

	save_curbuf = curbuf;
	curbuf = buf;

	if (*varname == '&')
	{
	    if (get_option_tv(&varname, rettv, TRUE) == OK)
		done = TRUE;
	}
	else if (STRCMP(varname, "changedtick") == 0)
	{
	    rettv->v_type = VAR_NUMBER;
	    rettv->vval.v_number = curbuf->b_changedtick;
	    done = TRUE;
	}
	else
	{


	    v = find_var_in_ht(&curbuf->b_vars->dv_hashtab,
							 'b', varname, FALSE);
	    if (v != NULL)
	    {
		copy_tv(&v->di_tv, rettv);
		done = TRUE;
	    }
	}


	curbuf = save_curbuf;
    }

    if (!done && argvars[2].v_type != VAR_UNKNOWN)

	copy_tv(&argvars[2], rettv);

    --emsg_off;
}
