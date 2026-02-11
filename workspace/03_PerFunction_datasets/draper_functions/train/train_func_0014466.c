isl_point_zero(__isl_take isl_space *dim)
{
	isl_vec *vec;

	if (!dim)
		return NULL;
	vec = isl_vec_alloc(dim->ctx, 1 + isl_space_dim(dim, isl_dim_all));
	if (!vec)
		goto error;
	isl_int_set_si(vec->el[0], 1);
	isl_seq_clr(vec->el + 1, vec->size - 1);
	return isl_point_alloc(dim, vec);
error:
	isl_space_free(dim);
	return NULL;
}
