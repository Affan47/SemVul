rbtree_next(t_rbtree_node *node)
{
	if (node->right != NULL) {
		node = node->right;
		while (node->left != NULL) {
			node = node->left;
		}
	} else {
		if (node->parent != NULL && (node == node->parent->left)) {
			node = node->parent;
		} else {
			while (node->parent != NULL && (node == node->parent->right)) {
				node = node->parent;
			}
			node = node->parent;
		}
	}

	return node;
}
