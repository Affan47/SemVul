isl_ast_graft_add_guard(
	__isl_take isl_ast_graft *graft,
	__isl_take isl_set *guard, __isl_keep isl_ast_build *build)
{
	isl_basic_set *enforced;

	if (!graft || !build)
		goto error;

	enforced = isl_basic_set_copy(graft->enforced);
	guard = isl_set_gist(guard, isl_set_from_basic_set(enforced));

	graft = store_guard(graft, guard, build);

	return graft;
error:
	isl_set_free(guard);
	isl_ast_graft_free(graft);
	return NULL;
}
