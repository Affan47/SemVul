avl_tree_to_array_add_subtree(AVLTreeNode *subtree,
                                         AVLTreeValue *array,
                                         int *index)
{
	if (subtree == NULL) {
		return;
	}


	avl_tree_to_array_add_subtree(subtree->children[AVL_TREE_NODE_LEFT],
	                              array, index);


	array[*index] = subtree->key;
	++*index;


	avl_tree_to_array_add_subtree(subtree->children[AVL_TREE_NODE_RIGHT],
	                              array, index);
}
