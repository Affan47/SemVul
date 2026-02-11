__data_result_print_cli(int fd, const struct ast_data *root, uint32_t depth)
{
	struct ao2_iterator iter;
	struct ast_data *node;

	if (root->type == AST_DATA_CONTAINER) {
		iter = ao2_iterator_init(root->children, 0);
		while ((node = ao2_iterator_next(&iter))) {
			data_result_print_cli_node(fd, node, depth + 1);
			ao2_ref(node, -1);
		}
		ao2_iterator_destroy(&iter);
	} else {
		data_result_print_cli_node(fd, root, depth);
	}
}
