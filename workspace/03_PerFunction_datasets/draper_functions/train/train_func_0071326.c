isl_local_space_get_dim_id(__isl_keep isl_local_space *ls,
	enum isl_dim_type type, unsigned pos)
{
	return ls ? isl_space_get_dim_id(ls->dim, type, pos) : NULL;
}
