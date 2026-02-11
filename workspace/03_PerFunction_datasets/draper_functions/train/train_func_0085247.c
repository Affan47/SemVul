append_ci_co_BB(Block* bptr, Module_table* mptr,
		const int* correspond_rev, int rev_num,
		const int* correspond_var, int var_num)
{
    IntSet  tmp_set;
    IntSet  in_set;
    IntSet  out_set;
    Pe_statement*  pe_stm;

    var_num = range_IntSet(bptr->pre_head->exposed_def);
    construct_IntSet(tmp_set, var_num);
    if (var_num != (int)range_IntSet(bptr->in_var_list->scalar_bv)) {
	construct_IntSet(in_set, var_num);
	construct_IntSet(out_set, var_num);
#ifdef  USE_IN_OUT
	fit_IntSet(in_set, bptr->df_info->scalar_live_in);
	fit_IntSet(out_set, bptr->df_info->scalar_live_out);
#else
	fit_IntSet(in_set, bptr->use_var_list->scalar_bv);
	fit_IntSet(out_set, bptr->def_var_list->scalar_bv);
#endif
    } else {
#ifdef  USE_IN_OUT
	in_set = bptr->df_info->scalar_live_in;
	out_set = bptr->df_info->scalar_live_out;
#else
	in_set = bptr->use_var_list->scalar_bv;
	out_set = bptr->def_var_list->scalar_bv;
#endif
    }
    for (pe_stm = bptr->pre_head; pe_stm != NULL; pe_stm = pe_stm->next) {
	Statement*  ci_stm;
	Statement*  co_stm;

	if (bptr->need_ci) {
	    Statement*  ci_point;

	    and_IntSet(tmp_set, pe_stm->propagated_use, in_set);
	    ci_stm = make_ci_co_statement(tmp_set, correspond_rev, rev_num,
					  mptr, pe_stm, TYPE_CI,
					  FALSE, TRUE);
	    ci_point = search_ci_point(pe_stm->stm_head);
	    insert_stm(pe_stm, ci_point, ci_stm);
	    clear_IntSet(tmp_set);
	}

	if (bptr->need_co) {
	    int  i;
	    int  min;
	    int  max;
	    Statement*  co_point;

	    assign_IntSet(tmp_set, out_set);
	    min = min_IntSet(tmp_set);
	    max = max_IntSet(tmp_set);
	    for (i = min; i <= max; i++) {
		if (in_IntSet(tmp_set, i) && correspond_var[i] > 0) {
		    add1_IntSet(tmp_set, correspond_var[i]);
		}
	    }
	    and_IntSet(tmp_set, tmp_set, pe_stm->propagated_def);
	    co_stm = make_ci_co_statement(tmp_set, correspond_rev, rev_num,
					  mptr, pe_stm, TYPE_CO,
					  FALSE, TRUE);
	    co_point = search_co_point(pe_stm->stm_head);
	    insert_stm(pe_stm, co_point, co_stm);
	    clear_IntSet(tmp_set);
	}
    }
    if (in_set != bptr->in_var_list->scalar_bv) {
	destruct_IntSet(in_set);
	destruct_IntSet(out_set);
    }
    destruct_IntSet(tmp_set);
}
