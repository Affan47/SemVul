f_synstack(argvars, rettv)
    typval_T	*argvars UNUSED;
    typval_T	*rettv;
{
#ifdef FEAT_SYN_HL
    long	lnum;
    long	col;
    int		i;
    int		id;
#endif

    rettv->v_type = VAR_LIST;
    rettv->vval.v_list = NULL;

#ifdef FEAT_SYN_HL
    lnum = get_tv_lnum(argvars);
    col = get_tv_number(&argvars[1]) - 1;

    if (lnum >= 1 && lnum <= curbuf->b_ml.ml_line_count
	    && col >= 0 && col <= (long)STRLEN(ml_get(lnum))
	    && rettv_list_alloc(rettv) != FAIL)
    {
	(void)syn_get_id(curwin, lnum, (colnr_T)col, FALSE, NULL, TRUE);
	for (i = 0; ; ++i)
	{
	    id = syn_get_stack_item(i);
	    if (id < 0)
		break;
	    if (list_append_number(rettv->vval.v_list, id) == FAIL)
		break;
	}
    }
#endif
}
