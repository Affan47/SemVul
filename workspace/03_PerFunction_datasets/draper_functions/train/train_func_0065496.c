isl_ast_build_get_space(__isl_keep isl_ast_build *build,
	int internal)
{
	int i;
	int dim;
	isl_space *space;

	if (!build)
		return NULL;

	space = isl_set_get_space(build->domain);
	if (internal)
		return space;

	if (!isl_ast_build_need_schedule_map(build))
		return space;

	dim = isl_set_dim(build->domain, isl_dim_set);
	space = isl_space_drop_dims(space, isl_dim_set,
				    build->depth, dim - build->depth);
	for (i = build->depth - 1; i >= 0; --i)
		if (isl_ast_build_has_affine_value(build, i))
			space = isl_space_drop_dims(space, isl_dim_set, i, 1);

	return space;
}
