isl_ast_expr_from_constraint(
	__isl_take isl_constraint *constraint, __isl_keep isl_ast_build *build)
{
	int i, n;
	isl_ctx *ctx;
	isl_ast_expr *expr_pos;
	isl_ast_expr *expr_neg;
	isl_ast_expr *expr;
	isl_aff *aff;
	isl_val *v;
	int eq;
	enum isl_ast_op_type type;

	if (!constraint)
		return NULL;

	aff = isl_constraint_get_aff(constraint);
	eq = isl_constraint_is_equality(constraint);
	isl_constraint_free(constraint);

	n = isl_aff_dim(aff, isl_dim_div);
	if (eq && n > 0)
		for (i = 0; i < n; ++i) {
			int is_stride;
			is_stride = is_stride_constraint(aff, i);
			if (is_stride < 0)
				goto error;
			if (is_stride)
				return extract_stride_constraint(aff, i, build);
		}

	ctx = isl_aff_get_ctx(aff);
	expr_pos = isl_ast_expr_alloc_int_si(ctx, 0);
	expr_neg = isl_ast_expr_alloc_int_si(ctx, 0);

	aff = extract_modulos(aff, &expr_pos, &expr_neg, build);

	expr_pos = add_signed_terms(expr_pos, aff, 1, build);
	expr_neg = add_signed_terms(expr_neg, aff, -1, build);

	v = isl_aff_get_constant_val(aff);
	if (constant_is_considered_positive(v, expr_pos, expr_neg)) {
		expr_pos = isl_ast_expr_add_int(expr_pos, v);
	} else {
		v = isl_val_neg(v);
		expr_neg = isl_ast_expr_add_int(expr_neg, v);
	}

	if (isl_ast_expr_get_type(expr_pos) == isl_ast_expr_int &&
	    isl_ast_expr_get_type(expr_neg) != isl_ast_expr_int) {
		type = eq ? isl_ast_op_eq : isl_ast_op_le;
		expr = isl_ast_expr_alloc_binary(type, expr_neg, expr_pos);
	} else {
		type = eq ? isl_ast_op_eq : isl_ast_op_ge;
		expr = isl_ast_expr_alloc_binary(type, expr_pos, expr_neg);
	}

	isl_aff_free(aff);
	return expr;
error:
	isl_aff_free(aff);
	return NULL;
}
