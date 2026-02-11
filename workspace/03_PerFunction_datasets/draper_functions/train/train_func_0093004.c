pos(__isl_keep isl_space *dim, enum isl_dim_type type)
{
	switch (type) {
	case isl_dim_param:	return 1;
	case isl_dim_in:	return 1 + dim->nparam;
	case isl_dim_out:	return 1 + dim->nparam + dim->n_in;
	default:		return 0;
	}
}
