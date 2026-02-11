binary_search_tree_traverse_in_order(Node* node, traversal_cb cb)
{
	if(node == NULL) {
		return;
	}

	binary_search_tree_traverse_in_order(node->left, cb);
	cb(node->data);
	binary_search_tree_traverse_in_order(node->right, cb);
}
