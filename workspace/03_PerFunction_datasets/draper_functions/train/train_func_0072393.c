isl_ast_build_expr_from_set(
	__isl_keep isl_ast_build *build, __isl_take isl_set *set)
{
	struct isl_expr_from_set_data data = { build, 1, NULL };

	if (isl_set_foreach_basic_set(set, &expr_from_set, &data) < 0)
		data.res = isl_ast_expr_free(data.res);

	isl_set_free(set);
	return data.res;
}
