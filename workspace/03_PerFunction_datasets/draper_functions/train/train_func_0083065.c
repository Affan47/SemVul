basic_map_partial_lexopt_symm_pma_core(
	__isl_take isl_basic_map *bmap, __isl_take isl_basic_set *dom,
	__isl_give isl_set **empty, int max, __isl_take isl_mat *cst,
	__isl_take isl_space *map_space, __isl_take isl_space *set_space)
{
	isl_pw_multi_aff *opt;
	isl_pw_aff *min_expr_pa;
	isl_set *min_expr;
	union isl_lex_res res;

	min_expr = set_minimum(isl_basic_set_get_space(dom), isl_mat_copy(cst));
	min_expr_pa = set_minimum_pa(isl_basic_set_get_space(dom),
					isl_mat_copy(cst));

	opt = basic_map_partial_lexopt_pma(bmap, dom, empty, max);

	if (empty) {
		*empty = split(*empty,
			       isl_set_copy(min_expr), isl_mat_copy(cst));
		*empty = isl_set_reset_space(*empty, set_space);
	}

	opt = split_domain_pma(opt, min_expr_pa, min_expr, cst);
	opt = isl_pw_multi_aff_reset_space(opt, map_space);

	res.pma = opt;
	return res;
}
