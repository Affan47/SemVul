opt_look_for_col_in_cond_before(

	ulint		cmp_type,
	ulint		col_no,
	func_node_t*	search_cond,
	sel_node_t*	sel_node,
	ulint		nth_table,


	ulint*		op)

{
	func_node_t*	new_cond;
	que_node_t*	exp;

	if (search_cond == NULL) {

		return(NULL);
	}

	ut_a(que_node_get_type(search_cond) == QUE_NODE_FUNC);
	ut_a(search_cond->func != PARS_OR_TOKEN);
	ut_a(search_cond->func != PARS_NOT_TOKEN);

	if (search_cond->func == PARS_AND_TOKEN) {
		new_cond = search_cond->args;

		exp = opt_look_for_col_in_cond_before(cmp_type, col_no,
						      new_cond, sel_node,
						      nth_table, op);
		if (exp) {

			return(exp);
		}

		new_cond = que_node_get_next(new_cond);

		exp = opt_look_for_col_in_cond_before(cmp_type, col_no,
						      new_cond, sel_node,
						      nth_table, op);
		return(exp);
	}

	exp = opt_look_for_col_in_comparison_before(cmp_type, col_no,
						    search_cond, sel_node,
						    nth_table, op);
	if (exp == NULL) {

		return(NULL);
	}


	if (sel_node->asc && ((*op == '<') || (*op == PARS_LE_TOKEN))) {

		return(NULL);

	} else if (!sel_node->asc
		   && ((*op == '>') || (*op == PARS_GE_TOKEN))) {

		return(NULL);
	}

	return(exp);
}
