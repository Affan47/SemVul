isl_space_extend_domain_with_range(
	__isl_take isl_space *space, __isl_take isl_space *model)
{
	if (!model)
		goto error;

	space = isl_space_from_domain(space);
	space = isl_space_add_dims(space, isl_dim_out,
				    isl_space_dim(model, isl_dim_out));
	if (isl_space_has_tuple_id(model, isl_dim_out))
		space = isl_space_set_tuple_id(space, isl_dim_out,
				isl_space_get_tuple_id(model, isl_dim_out));
	if (!space)
		goto error;
	if (model->nested[1]) {
		isl_space *nested = isl_space_copy(model->nested[1]);
		int n_nested, n_space;
		nested = isl_space_align_params(nested, isl_space_copy(space));
		n_nested = isl_space_dim(nested, isl_dim_param);
		n_space = isl_space_dim(space, isl_dim_param);
		if (n_nested > n_space)
			nested = isl_space_drop_dims(nested, isl_dim_param,
						n_space, n_nested - n_space);
		if (!nested)
			goto error;
		space->nested[1] = nested;
	}
	isl_space_free(model);
	return space;
error:
	isl_space_free(model);
	isl_space_free(space);
	return NULL;
}
