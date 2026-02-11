mark_as_set(__isl_take isl_space *space)
{
	space = isl_space_cow(space);
	if (!space)
		return NULL;
	space = isl_space_set_tuple_id(space, isl_dim_in, &isl_id_none);
	return space;
}
