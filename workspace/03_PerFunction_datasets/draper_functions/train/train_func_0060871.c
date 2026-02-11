isl_space_as_set_space(__isl_take isl_space *dim)
{
	dim = isl_space_cow(dim);
	if (!dim)
		return NULL;

	dim->n_out += dim->n_in;
	dim->n_in = 0;
	dim = isl_space_reset(dim, isl_dim_in);
	dim = isl_space_reset(dim, isl_dim_out);

	return dim;
}
