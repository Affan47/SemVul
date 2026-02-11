isl_ast_build_expr_from_basic_set(
	 __isl_keep isl_ast_build *build, __isl_take isl_basic_set *bset)
{
	struct isl_expr_from_basic_data data = { build, 1, NULL };

	if (isl_basic_set_foreach_constraint(bset,
					    &expr_from_basic_set, &data) < 0) {
		data.res = isl_ast_expr_free(data.res);
	} else if (data.res == NULL) {
		isl_ctx *ctx = isl_basic_set_get_ctx(bset);
		data.res = isl_ast_expr_alloc_int_si(ctx, 1);
	}

	isl_basic_set_free(bset);
	return data.res;
}
