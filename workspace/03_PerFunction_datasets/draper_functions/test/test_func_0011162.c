isl_ast_expr_from_aff(__isl_take isl_aff *aff,
	__isl_keep isl_ast_build *build)
{
	int i, j;
	int n;
	isl_val *v, *d;
	isl_ctx *ctx = isl_aff_get_ctx(aff);
	isl_ast_expr *expr, *expr_neg;
	enum isl_dim_type t[] = { isl_dim_param, isl_dim_in, isl_dim_div };
	enum isl_dim_type l[] = { isl_dim_param, isl_dim_set, isl_dim_div };
	isl_local_space *ls;

	if (!aff)
		return NULL;

	expr = isl_ast_expr_alloc_int_si(ctx, 0);
	expr_neg = isl_ast_expr_alloc_int_si(ctx, 0);

	d = isl_aff_get_denominator_val(aff);
	aff = isl_aff_scale_val(aff, isl_val_copy(d));

	aff = extract_modulos(aff, &expr, &expr_neg, build);
	expr = ast_expr_sub(expr, expr_neg);

	ls = isl_aff_get_domain_local_space(aff);

	for (i = 0; i < 3; ++i) {
		n = isl_aff_dim(aff, t[i]);
		for (j = 0; j < n; ++j) {
			v = isl_aff_get_coefficient_val(aff, t[i], j);
			if (!v)
				expr = isl_ast_expr_free(expr);
			if (isl_val_is_zero(v)) {
				isl_val_free(v);
				continue;
			}
			expr = isl_ast_expr_add_term(expr,
							ls, l[i], j, v, build);
		}
	}

	v = isl_aff_get_constant_val(aff);
	expr = isl_ast_expr_add_int(expr, v);

	if (!isl_val_is_one(d))
		expr = isl_ast_expr_div(expr, isl_ast_expr_from_val(d));
	else
		isl_val_free(d);

	isl_local_space_free(ls);
	isl_aff_free(aff);
	return expr;
}
