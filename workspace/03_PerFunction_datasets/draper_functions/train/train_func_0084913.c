bernstein_coefficients_base(
	__isl_take isl_basic_set *bset,
	__isl_take isl_qpolynomial *poly, struct bernstein_data *data, int *tight)
{
	unsigned nvar;
	isl_space *dim;
	isl_pw_qpolynomial_fold *pwf;
	isl_vertices *vertices;
	int covers;

	nvar = isl_basic_set_dim(bset, isl_dim_set);
	if (nvar == 0) {
		isl_set *dom;
		isl_qpolynomial_fold *fold;

		fold = isl_qpolynomial_fold_alloc(data->type, poly);
		dom = isl_set_from_basic_set(bset);
		if (tight)
			*tight = 1;
		pwf = isl_pw_qpolynomial_fold_alloc(data->type, dom, fold);
		return isl_pw_qpolynomial_fold_project_domain_on_params(pwf);
	}

	if (isl_qpolynomial_is_zero(poly)) {
		isl_set *dom;
		isl_qpolynomial_fold *fold;
		fold = isl_qpolynomial_fold_alloc(data->type, poly);
		dom = isl_set_from_basic_set(bset);
		pwf = isl_pw_qpolynomial_fold_alloc(data->type, dom, fold);
		if (tight)
			*tight = 1;
		return isl_pw_qpolynomial_fold_project_domain_on_params(pwf);
	}

	dim = isl_basic_set_get_space(bset);
	dim = isl_space_params(dim);
	dim = isl_space_from_domain(dim);
	dim = isl_space_add_dims(dim, isl_dim_set, 1);
	data->pwf = isl_pw_qpolynomial_fold_zero(isl_space_copy(dim), data->type);
	data->pwf_tight = isl_pw_qpolynomial_fold_zero(dim, data->type);
	data->poly = isl_qpolynomial_homogenize(isl_qpolynomial_copy(poly));
	vertices = isl_basic_set_compute_vertices(bset);
	isl_vertices_foreach_disjoint_cell(vertices,
		&bernstein_coefficients_cell, data);
	isl_vertices_free(vertices);
	isl_qpolynomial_free(data->poly);

	isl_basic_set_free(bset);
	isl_qpolynomial_free(poly);

	covers = isl_pw_qpolynomial_fold_covers(data->pwf_tight, data->pwf);
	if (covers < 0)
		goto error;

	if (tight)
		*tight = covers;

	if (covers) {
		isl_pw_qpolynomial_fold_free(data->pwf);
		return data->pwf_tight;
	}

	data->pwf = isl_pw_qpolynomial_fold_fold(data->pwf, data->pwf_tight);

	return data->pwf;
error:
	isl_pw_qpolynomial_fold_free(data->pwf_tight);
	isl_pw_qpolynomial_fold_free(data->pwf);
	return NULL;
}
