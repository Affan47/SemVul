solve_ilp(struct isl_basic_set *bset,
				      isl_int *f, isl_int *opt,
				      struct isl_vec **sol_p)
{
	enum isl_lp_result res;
	isl_int l, u;
	struct isl_vec *sol;

	res = isl_basic_set_solve_lp(bset, 0, f, bset->ctx->one,
					opt, NULL, &sol);
	if (res == isl_lp_ok && isl_int_is_one(sol->el[0])) {
		if (sol_p)
			*sol_p = sol;
		else
			isl_vec_free(sol);
		return isl_lp_ok;
	}
	isl_vec_free(sol);
	if (res == isl_lp_error || res == isl_lp_empty)
		return res;

	sol = initial_solution(bset, f);
	if (!sol)
		return isl_lp_error;
	if (sol->size == 0) {
		isl_vec_free(sol);
		return isl_lp_empty;
	}
	if (res == isl_lp_unbounded) {
		isl_vec_free(sol);
		return isl_lp_unbounded;
	}

	isl_int_init(l);
	isl_int_init(u);

	isl_int_set(l, *opt);

	isl_seq_inner_product(f, sol->el, sol->size, opt);
	isl_int_sub_ui(u, *opt, 1);

	sol = solve_ilp_search(bset, f, opt, sol, l, u);
	if (!sol)
		res = isl_lp_error;

	isl_int_clear(l);
	isl_int_clear(u);

	if (sol_p)
		*sol_p = sol;
	else
		isl_vec_free(sol);

	return res;
}
