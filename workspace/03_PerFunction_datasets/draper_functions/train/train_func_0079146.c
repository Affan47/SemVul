avl_tree_node_replace(AVLTree *tree, AVLTreeNode *node1,
                                  AVLTreeNode *node2)
{
	int side;


	if (node2 != NULL) {
		node2->parent = node1->parent;
	}


	if (node1->parent == NULL) {
		tree->root_node = node2;
	} else {
		side = avl_tree_node_parent_side(node1);
		node1->parent->children[side] = node2;

		avl_tree_update_height(node1->parent);
	}
}
