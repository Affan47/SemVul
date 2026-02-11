avl_tree_lookup_node(AVLTree *tree, AVLTreeKey key)
{
	AVLTreeNode *node;
	int diff;


	node = tree->root_node;

	while (node != NULL) {

		diff = tree->compare_func(key, node->key);

		if (diff == 0) {


			return node;

		} else if (diff < 0) {
			node = node->children[AVL_TREE_NODE_LEFT];
		} else {
			node = node->children[AVL_TREE_NODE_RIGHT];
		}
	}


	return NULL;
}
