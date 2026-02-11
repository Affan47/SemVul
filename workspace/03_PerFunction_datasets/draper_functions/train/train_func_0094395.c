insert_pending_guard_node(
	__isl_take isl_ast_graft *graft, __isl_keep isl_ast_build *build)
{
	if (!graft)
		return NULL;

	return insert_if_node(graft, isl_set_copy(graft->guard), build);
}
