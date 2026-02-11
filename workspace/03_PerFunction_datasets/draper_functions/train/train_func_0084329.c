multi_union_pw_aff_apply_aff(
	__isl_take isl_multi_union_pw_aff *mupa, __isl_take isl_aff *aff)
{
	int i, n_in, n_div;
	isl_union_pw_aff *upa;
	isl_union_set *uset;
	isl_val *v;
	isl_aff *cst;

	n_in = isl_aff_dim(aff, isl_dim_in);
	n_div = isl_aff_dim(aff, isl_dim_div);

	uset = isl_multi_union_pw_aff_domain(isl_multi_union_pw_aff_copy(mupa));
	cst = isl_aff_copy(aff);
	cst = isl_aff_drop_dims(cst, isl_dim_div, 0, n_div);
	cst = isl_aff_drop_dims(cst, isl_dim_in, 0, n_in);
	cst = isl_aff_project_domain_on_params(cst);
	upa = isl_union_pw_aff_aff_on_domain(uset, cst);

	for (i = 0; i < n_in; ++i) {
		isl_union_pw_aff *upa_i;

		if (!isl_aff_involves_dims(aff, isl_dim_in, i, 1))
			continue;
		v = isl_aff_get_coefficient_val(aff, isl_dim_in, i);
		upa_i = isl_multi_union_pw_aff_get_union_pw_aff(mupa, i);
		upa_i = isl_union_pw_aff_scale_val(upa_i, v);
		upa = isl_union_pw_aff_add(upa, upa_i);
	}

	for (i = 0; i < n_div; ++i) {
		isl_aff *div;
		isl_union_pw_aff *upa_i;

		if (!isl_aff_involves_dims(aff, isl_dim_div, i, 1))
			continue;
		div = isl_aff_get_div(aff, i);
		upa_i = multi_union_pw_aff_apply_aff(
					isl_multi_union_pw_aff_copy(mupa), div);
		upa_i = isl_union_pw_aff_floor(upa_i);
		v = isl_aff_get_coefficient_val(aff, isl_dim_div, i);
		upa_i = isl_union_pw_aff_scale_val(upa_i, v);
		upa = isl_union_pw_aff_add(upa, upa_i);
	}

	isl_multi_union_pw_aff_free(mupa);
	isl_aff_free(aff);

	return upa;
}
