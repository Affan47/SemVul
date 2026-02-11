has_sign(__isl_keep isl_basic_set *bset,
	__isl_keep isl_qpolynomial *poly, int sign, int *signs)
{
	struct range_data data_m;
	unsigned nparam;
	isl_space *dim;
	isl_val *opt;
	int r;
	enum isl_fold type;

	nparam = isl_basic_set_dim(bset, isl_dim_param);

	bset = isl_basic_set_copy(bset);
	poly = isl_qpolynomial_copy(poly);

	bset = isl_basic_set_move_dims(bset, isl_dim_set, 0,
					isl_dim_param, 0, nparam);
	poly = isl_qpolynomial_move_dims(poly, isl_dim_in, 0,
					isl_dim_param, 0, nparam);

	dim = isl_qpolynomial_get_space(poly);
	dim = isl_space_params(dim);
	dim = isl_space_from_domain(dim);
	dim = isl_space_add_dims(dim, isl_dim_out, 1);

	data_m.test_monotonicity = 0;
	data_m.signs = signs;
	data_m.sign = -sign;
	type = data_m.sign < 0 ? isl_fold_min : isl_fold_max;
	data_m.pwf = isl_pw_qpolynomial_fold_zero(dim, type);
	data_m.tight = 0;
	data_m.pwf_tight = NULL;

	if (propagate_on_domain(bset, poly, &data_m) < 0)
		goto error;

	if (sign > 0)
		opt = isl_pw_qpolynomial_fold_min(data_m.pwf);
	else
		opt = isl_pw_qpolynomial_fold_max(data_m.pwf);

	if (!opt)
		r = -1;
	else if (isl_val_is_nan(opt) ||
		 isl_val_is_infty(opt) ||
		 isl_val_is_neginfty(opt))
		r = 0;
	else
		r = sign * isl_val_sgn(opt) >= 0;

	isl_val_free(opt);

	return r;
error:
	isl_pw_qpolynomial_fold_free(data_m.pwf);
	return -1;
}
