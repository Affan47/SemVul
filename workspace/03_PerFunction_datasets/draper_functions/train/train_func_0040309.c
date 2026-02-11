isl_ast_build_set_loop_bounds(
	__isl_take isl_ast_build *build, __isl_take isl_basic_set *bounds)
{
	isl_set *set;

	build = isl_ast_build_cow(build);
	if (!build)
		goto error;

	bounds = isl_basic_set_preimage_multi_aff(bounds,
					isl_multi_aff_copy(build->values));
	build = update_values(build, isl_basic_set_copy(bounds));
	if (!build)
		goto error;
	set = isl_set_from_basic_set(isl_basic_set_copy(bounds));
	if (isl_ast_build_has_affine_value(build, build->depth)) {
		set = isl_set_eliminate(set, isl_dim_set, build->depth, 1);
		set = isl_set_compute_divs(set);
		build->pending = isl_set_intersect(build->pending,
							isl_set_copy(set));
		build->domain = isl_set_intersect(build->domain, set);
	} else {
		isl_basic_set *generated, *pending;

		pending = isl_basic_set_copy(bounds);
		pending = isl_basic_set_drop_constraints_involving_dims(pending,
					isl_dim_set, build->depth, 1);
		build->pending = isl_set_intersect(build->pending,
					isl_set_from_basic_set(pending));
		generated = isl_basic_set_copy(bounds);
		generated = isl_basic_set_drop_constraints_not_involving_dims(
				    generated, isl_dim_set, build->depth, 1);
		build->generated = isl_set_intersect(build->generated,
					isl_set_from_basic_set(generated));
		build->domain = isl_set_intersect(build->domain, set);
		build = isl_ast_build_include_stride(build);
		if (!build)
			goto error;
	}
	isl_basic_set_free(bounds);

	if (!build->domain || !build->pending || !build->generated)
		return isl_ast_build_free(build);

	return build;
error:
	isl_ast_build_free(build);
	isl_basic_set_free(bounds);
	return NULL;
}
