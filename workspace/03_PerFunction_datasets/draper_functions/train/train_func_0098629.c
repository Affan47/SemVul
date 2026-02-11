tree_traverse(tree_t* root, unsigned int depth, node_callback_t cb) {
	int status;

	if (root->left)
		status  = tree_traverse(root->left, depth + 1, cb);

	if (root->right)
		status += tree_traverse(root->right, depth + 1, cb);


	status += cb(root, depth);

	return status;
}
