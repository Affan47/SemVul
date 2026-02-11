isl_space_has_equal_tuples(__isl_keep isl_space *space1,
	__isl_keep isl_space *space2)
{
	if (!space1 || !space2)
		return -1;
	if (space1 == space2)
		return 1;
	return isl_space_tuple_is_equal(space1, isl_dim_in,
					space2, isl_dim_in) &&
	       isl_space_tuple_is_equal(space1, isl_dim_out,
					space2, isl_dim_out);
}
