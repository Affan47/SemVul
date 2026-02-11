f_complete(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
    int	    startcol;

    if ((State & INSERT) == 0)
    {
	EMSG(_("E785: complete() can only be used in Insert mode"));
	return;
    }


    if (!undo_allowed())
	return;

    if (argvars[1].v_type != VAR_LIST || argvars[1].vval.v_list == NULL)
    {
	EMSG(_(e_invarg));
	return;
    }

    startcol = get_tv_number_chk(&argvars[0], NULL);
    if (startcol <= 0)
	return;

    set_completion(startcol - 1, argvars[1].vval.v_list);
}
