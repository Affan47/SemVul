isl_multi_pw_aff_apply_aff_aligned(
	__isl_take isl_multi_pw_aff *mpa, __isl_take isl_aff *aff)
{
	int i, n_param, n_in, n_div;
	isl_space *space;
	isl_val *v;
	isl_pw_aff *pa;
	isl_aff *tmp;

	n_param = isl_aff_dim(aff, isl_dim_param);
	n_in = isl_aff_dim(aff, isl_dim_in);
	n_div = isl_aff_dim(aff, isl_dim_div);

	space = isl_space_domain(isl_multi_pw_aff_get_space(mpa));
	tmp = isl_aff_copy(aff);
	tmp = isl_aff_drop_dims(tmp, isl_dim_div, 0, n_div);
	tmp = isl_aff_drop_dims(tmp, isl_dim_in, 0, n_in);
	tmp = isl_aff_add_dims(tmp, isl_dim_in,
				isl_space_dim(space, isl_dim_set));
	tmp = isl_aff_reset_domain_space(tmp, space);
	pa = isl_pw_aff_from_aff(tmp);

	for (i = 0; i < n_in; ++i) {
		isl_pw_aff *pa_i;

		if (!isl_aff_involves_dims(aff, isl_dim_in, i, 1))
			continue;
		v = isl_aff_get_coefficient_val(aff, isl_dim_in, i);
		pa_i = isl_multi_pw_aff_get_pw_aff(mpa, i);
		pa_i = isl_pw_aff_scale_val(pa_i, v);
		pa = isl_pw_aff_add(pa, pa_i);
	}

	for (i = 0; i < n_div; ++i) {
		isl_aff *div;
		isl_pw_aff *pa_i;

		if (!isl_aff_involves_dims(aff, isl_dim_div, i, 1))
			continue;
		div = isl_aff_get_div(aff, i);
		pa_i = isl_multi_pw_aff_apply_aff_aligned(
					    isl_multi_pw_aff_copy(mpa), div);
		pa_i = isl_pw_aff_floor(pa_i);
		v = isl_aff_get_coefficient_val(aff, isl_dim_div, i);
		pa_i = isl_pw_aff_scale_val(pa_i, v);
		pa = isl_pw_aff_add(pa, pa_i);
	}

	isl_multi_pw_aff_free(mpa);
	isl_aff_free(aff);

	return pa;
}
