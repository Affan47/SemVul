parameter_compute_divs(struct isl_basic_set *bset)
{
	int i;
	struct isl_mat *eq;
	struct isl_mat *T, *T2;
	struct isl_set *set;
	unsigned nparam;

	bset = isl_basic_set_cow(bset);
	if (!bset)
		return NULL;

	if (bset->n_eq == 0)
		return base_compute_divs(bset);

	bset = isl_basic_set_gauss(bset, NULL);
	if (!bset)
		return NULL;
	if (isl_basic_set_plain_is_empty(bset))
		return isl_set_from_basic_set(bset);

	i = first_parameter_equality(bset);
	if (i == bset->n_eq)
		return base_compute_divs(bset);

	nparam = isl_basic_set_dim(bset, isl_dim_param);
	eq = isl_mat_sub_alloc6(bset->ctx, bset->eq, i, bset->n_eq - i,
		0, 1 + nparam);
	eq = isl_mat_cow(eq);
	T = isl_mat_variable_compression(isl_mat_copy(eq), &T2);
	if (T && T->n_col == 0) {
		isl_mat_free(T);
		isl_mat_free(T2);
		isl_mat_free(eq);
		bset = isl_basic_set_set_to_empty(bset);
		return isl_set_from_basic_set(bset);
	}
	bset = basic_set_parameter_preimage(bset, T);

	i = first_parameter_equality(bset);
	if (!bset)
		set = NULL;
	else if (i == bset->n_eq)
		set = base_compute_divs(bset);
	else
		set = parameter_compute_divs(bset);
	set = set_parameter_preimage(set, T2);
	set = set_append_equalities(set, eq);
	return set;
}
