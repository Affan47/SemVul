tree_node_has_dummy_child (TreeNode *node)
{
	return (node->directory != NULL
		&& (!node->done_loading
		    || node->first_child == NULL
		    || node->force_has_dummy)) ||

		(node->directory == NULL && node->parent == NULL);
}
