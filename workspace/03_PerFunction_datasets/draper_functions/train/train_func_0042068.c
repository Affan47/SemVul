f_undotree(argvars, rettv)
    typval_T	*argvars UNUSED;
    typval_T	*rettv;
{
    if (rettv_dict_alloc(rettv) == OK)
    {
	dict_T *dict = rettv->vval.v_dict;
	list_T *list;

	dict_add_nr_str(dict, "synced", (long)curbuf->b_u_synced, NULL);
	dict_add_nr_str(dict, "seq_last", curbuf->b_u_seq_last, NULL);
	dict_add_nr_str(dict, "save_last",
					(long)curbuf->b_u_save_nr_last, NULL);
	dict_add_nr_str(dict, "seq_cur", curbuf->b_u_seq_cur, NULL);
	dict_add_nr_str(dict, "time_cur", (long)curbuf->b_u_time_cur, NULL);
	dict_add_nr_str(dict, "save_cur", (long)curbuf->b_u_save_nr_cur, NULL);

	list = list_alloc();
	if (list != NULL)
	{
	    u_eval_tree(curbuf->b_u_oldhead, list);
	    dict_add_list(dict, "entries", list);
	}
    }
}
