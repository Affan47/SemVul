isl_ast_build_product(
	__isl_take isl_ast_build *build, __isl_take isl_space *space)
{
	isl_ctx *ctx;
	isl_vec *strides;
	isl_set *set;
	isl_multi_aff *embedding;
	int dim, n_it;

	build = isl_ast_build_cow(build);
	if (!build)
		goto error;

	build->outer_pos = build->depth;

	ctx = isl_ast_build_get_ctx(build);
	dim = isl_set_dim(build->domain, isl_dim_set);
	dim += isl_space_dim(space, isl_dim_set);
	n_it = isl_id_list_n_id(build->iterators);
	if (n_it < dim) {
		isl_id_list *l;
		l = generate_names(ctx, dim - n_it, n_it, build);
		build->iterators = isl_id_list_concat(build->iterators, l);
	}

	if (isl_set_is_params(build->domain))
		return isl_ast_build_init(build, space);

	set = isl_set_universe(isl_space_copy(space));
	build->domain = isl_set_product(build->domain, isl_set_copy(set));
	build->pending = isl_set_product(build->pending, isl_set_copy(set));
	build->generated = isl_set_product(build->generated, set);

	strides = isl_vec_alloc(ctx, isl_space_dim(space, isl_dim_set));
	strides = isl_vec_set_si(strides, 1);
	build->strides = isl_vec_concat(build->strides, strides);

	space = isl_space_map_from_set(space);
	build->offsets = isl_multi_aff_align_params(build->offsets,
						    isl_space_copy(space));
	build->offsets = isl_multi_aff_product(build->offsets,
				isl_multi_aff_zero(isl_space_copy(space)));
	build->values = isl_multi_aff_align_params(build->values,
						    isl_space_copy(space));
	embedding = isl_multi_aff_identity(space);
	build->values = isl_multi_aff_product(build->values,
					isl_multi_aff_copy(embedding));
	if (build->internal2input) {
		build->internal2input =
			isl_multi_aff_product(build->internal2input, embedding);
		build->internal2input =
			isl_multi_aff_flatten_range(build->internal2input);
		if (!build->internal2input)
			return isl_ast_build_free(build);
	} else {
		isl_multi_aff_free(embedding);
	}

	space = isl_ast_build_get_space(build, 1);
	build->options = embed_options(build->options, space);

	if (!build->iterators || !build->domain || !build->generated ||
	    !build->pending || !build->values ||
	    !build->strides || !build->offsets || !build->options)
		return isl_ast_build_free(build);

	return build;
error:
	isl_ast_build_free(build);
	isl_space_free(space);
	return NULL;
}
