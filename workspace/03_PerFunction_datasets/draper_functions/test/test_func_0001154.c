affine_hull_with_cone(struct isl_basic_set *bset,
	struct isl_basic_set *cone)
{
	unsigned total;
	unsigned cone_dim;
	struct isl_basic_set *hull;
	struct isl_mat *M, *U, *Q;

	if (!bset || !cone)
		goto error;

	total = isl_basic_set_total_dim(cone);
	cone_dim = total - cone->n_eq;

	M = isl_mat_sub_alloc6(bset->ctx, cone->eq, 0, cone->n_eq, 1, total);
	M = isl_mat_left_hermite(M, 0, &U, &Q);
	if (!M)
		goto error;
	isl_mat_free(M);

	U = isl_mat_lin_to_aff(U);
	bset = isl_basic_set_preimage(bset, isl_mat_copy(U));

	bset = isl_basic_set_drop_constraints_involving(bset, total - cone_dim,
							cone_dim);
	bset = isl_basic_set_drop_dims(bset, total - cone_dim, cone_dim);

	Q = isl_mat_lin_to_aff(Q);
	Q = isl_mat_drop_rows(Q, 1 + total - cone_dim, cone_dim);

	if (bset && bset->sample && bset->sample->size == 1 + total)
		bset->sample = isl_mat_vec_product(isl_mat_copy(Q), bset->sample);

	hull = uset_affine_hull_bounded(bset);

	if (!hull) {
		isl_mat_free(Q);
		isl_mat_free(U);
	} else {
		struct isl_vec *sample = isl_vec_copy(hull->sample);
		U = isl_mat_drop_cols(U, 1 + total - cone_dim, cone_dim);
		if (sample && sample->size > 0)
			sample = isl_mat_vec_product(U, sample);
		else
			isl_mat_free(U);
		hull = isl_basic_set_preimage(hull, Q);
		if (hull) {
			isl_vec_free(hull->sample);
			hull->sample = sample;
		} else
			isl_vec_free(sample);
	}

	isl_basic_set_free(cone);

	return hull;
error:
	isl_basic_set_free(bset);
	isl_basic_set_free(cone);
	return NULL;
}
