extract_modulos(__isl_take isl_aff *aff,
	__isl_keep isl_ast_expr **pos, __isl_keep isl_ast_expr **neg,
	__isl_keep isl_ast_build *build)
{
	isl_ctx *ctx;
	int j, n;

	if (!aff)
		return NULL;

	ctx = isl_aff_get_ctx(aff);
	if (!isl_options_get_ast_build_prefer_pdiv(ctx))
		return aff;

	n = isl_aff_dim(aff, isl_dim_div);
	for (j = 0; j < n; ++j) {
		isl_val *v;

		v = isl_aff_get_coefficient_val(aff, isl_dim_div, j);
		if (!v)
			return isl_aff_free(aff);
		if (isl_val_is_zero(v) ||
		    isl_val_is_one(v) || isl_val_is_negone(v)) {
			isl_val_free(v);
			continue;
		}
		aff = extract_modulo(aff, pos, neg, build, j, v);
		if (!aff)
			break;
	}

	return aff;
}
