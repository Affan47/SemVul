index_destroy(struct index_node *node)
{
	int c;

	for (c = node->first; c <= node->last; c++) {
		struct index_node *child = node->children[c];

		if (child)
			index_destroy(child);
	}
	index_values_free(node->values);
	free(node->prefix);
	free(node);
}
