store_guard(__isl_take isl_ast_graft *graft,
	__isl_take isl_set *guard, __isl_keep isl_ast_build *build)
{
	int is_universe;

	if (!graft)
		goto error;

	is_universe = isl_set_plain_is_universe(guard);
	if (is_universe < 0)
		goto error;
	if (is_universe) {
		isl_set_free(guard);
		return graft;
	}

	graft->guard = isl_set_intersect(graft->guard, guard);
	graft->guard = isl_ast_build_compute_gist(build, graft->guard);
	if (!graft->guard)
		return isl_ast_graft_free(graft);

	return graft;
error:
	isl_set_free(guard);
	return isl_ast_graft_free(graft);
}
