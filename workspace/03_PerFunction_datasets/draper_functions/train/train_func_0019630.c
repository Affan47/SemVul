data_search_cmp_char(const struct ast_data_search *root, const char *name,
	char value)
{
	struct ast_data_search *child;
	char node_value;
	enum data_search_comparison cmp_type;

	child = data_search_get_node(root, name);
	if (!child) {
		return 0;
	}

	node_value = *(child->value);
	cmp_type = child->cmp_type;

	ao2_ref(child, -1);

	return data_search_comparison_result(value - node_value, cmp_type);
}
