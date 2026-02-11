isl_space_get_tuple_name(__isl_keep isl_space *dim,
	 enum isl_dim_type type)
{
	isl_id *id;
	if (!dim)
		return NULL;
	if (type != isl_dim_in && type != isl_dim_out)
		return NULL;
	id = dim->tuple_id[type - isl_dim_in];
	return id ? id->name : NULL;
}
