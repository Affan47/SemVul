for_inc(__isl_keep isl_ast_build *build)
{
	int depth;
	isl_int v;
	isl_ctx *ctx;
	isl_ast_expr *inc;

	if (!build)
		return NULL;
	ctx = isl_ast_build_get_ctx(build);
	depth = isl_ast_build_get_depth(build);

	if (!isl_ast_build_has_stride(build, depth))
		return isl_ast_expr_alloc_int_si(ctx, 1);

	isl_int_init(v);
	isl_ast_build_get_stride(build, depth, &v);
	inc = isl_ast_expr_alloc_int(ctx, v);
	isl_int_clear(v);

	return inc;
}
