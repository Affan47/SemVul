isl_ast_expr_mod(__isl_keep isl_val *v,
	__isl_keep isl_aff *aff, __isl_keep isl_val *d,
	__isl_keep isl_ast_build *build)
{
	isl_ctx *ctx;
	isl_ast_expr *expr;
	isl_ast_expr *c;

	if (!aff)
		return NULL;

	ctx = isl_aff_get_ctx(aff);
	expr = isl_ast_expr_from_aff(isl_aff_copy(aff), build);

	c = isl_ast_expr_from_val(isl_val_copy(d));
	expr = isl_ast_expr_alloc_binary(isl_ast_op_pdiv_r, expr, c);

	if (!isl_val_is_one(v)) {
		c = isl_ast_expr_from_val(isl_val_copy(v));
		expr = isl_ast_expr_mul(c, expr);
	}

	return expr;
}
