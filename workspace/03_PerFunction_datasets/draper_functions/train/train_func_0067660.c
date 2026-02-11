tree_age_node(struct tree *tree, struct tree_node *node)
{
	node->u.playouts /= tree->ltree_aging;
	if (node->parent && !node->u.playouts) {
		struct tree_node *sibling = node->sibling;

		tree_unlink_node(node);
		tree_done_node(tree, node);
		return sibling;
	}

	struct tree_node *ni = node->children;
	while (ni) ni = tree_age_node(tree, ni);
	return node->sibling;
}
