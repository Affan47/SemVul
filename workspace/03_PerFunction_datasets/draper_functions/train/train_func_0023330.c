isl_ast_build_init_derived(
	__isl_take isl_ast_build *build, __isl_take isl_space *space)
{
	isl_ctx *ctx;
	isl_vec *strides;

	build = isl_ast_build_cow(build);
	if (!build || !build->domain)
		goto error;

	ctx = isl_ast_build_get_ctx(build);
	strides = isl_vec_alloc(ctx, isl_space_dim(space, isl_dim_set));
	strides = isl_vec_set_si(strides, 1);

	isl_vec_free(build->strides);
	build->strides = strides;

	space = isl_space_map_from_set(space);
	isl_multi_aff_free(build->offsets);
	build->offsets = isl_multi_aff_zero(isl_space_copy(space));
	isl_multi_aff_free(build->values);
	build->values = isl_multi_aff_identity(isl_space_copy(space));
	isl_multi_aff_free(build->internal2input);
	build->internal2input = isl_multi_aff_identity(space);

	if (!build->iterators || !build->domain || !build->generated ||
	    !build->pending || !build->values || !build->internal2input ||
	    !build->strides || !build->offsets || !build->options)
		return isl_ast_build_free(build);

	return build;
error:
	isl_space_free(space);
	return isl_ast_build_free(build);
}
