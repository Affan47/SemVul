f_glob(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
    int		flags = WILD_SILENT|WILD_USE_NL;
    expand_T	xpc;
    int		error = FALSE;


    if (argvars[1].v_type != VAR_UNKNOWN
				&& get_tv_number_chk(&argvars[1], &error))
	flags |= WILD_KEEP_ALL;
    rettv->v_type = VAR_STRING;
    if (!error)
    {
	ExpandInit(&xpc);
	xpc.xp_context = EXPAND_FILES;
	rettv->vval.v_string = ExpandOne(&xpc, get_tv_string(&argvars[0]),
						       NULL, flags, WILD_ALL);
    }
    else
	rettv->vval.v_string = NULL;
}
