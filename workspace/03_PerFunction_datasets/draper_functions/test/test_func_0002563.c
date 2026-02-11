tree_destructor(trbt_tree_t *tree)
{
	trbt_node_t *node;

	if (tree == NULL) {
		return 0;
	}

	node=tree->root;
	if (node == NULL) {
		return 0;
	}


	tree_destructor_traverse_node(node);

	return 0;
}
