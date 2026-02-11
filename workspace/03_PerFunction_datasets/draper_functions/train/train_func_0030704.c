isl_ast_expr_dup(__isl_keep isl_ast_expr *expr)
{
	int i;
	isl_ctx *ctx;
	isl_ast_expr *dup;

	if (!expr)
		return NULL;

	ctx = isl_ast_expr_get_ctx(expr);
	switch (expr->type) {
	case isl_ast_expr_int:
		dup = isl_ast_expr_from_val(isl_val_copy(expr->u.v));
		break;
	case isl_ast_expr_id:
		dup = isl_ast_expr_from_id(isl_id_copy(expr->u.id));
		break;
	case isl_ast_expr_op:
		dup = isl_ast_expr_alloc_op(ctx,
					    expr->u.op.op, expr->u.op.n_arg);
		if (!dup)
			return NULL;
		for (i = 0; i < expr->u.op.n_arg; ++i)
			dup->u.op.args[i] =
				isl_ast_expr_copy(expr->u.op.args[i]);
		break;
	case isl_ast_expr_error:
		dup = NULL;
	}

	if (!dup)
		return NULL;

	return dup;
}
