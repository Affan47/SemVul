isl_ast_node_from_ast_node_list(
	__isl_take isl_ast_node_list *list)
{
	isl_ast_node *node;

	if (isl_ast_node_list_n_ast_node(list) != 1)
		return isl_ast_node_alloc_block(list);

	node = isl_ast_node_list_get_ast_node(list, 0);
	isl_ast_node_list_free(list);

	return node;
}
