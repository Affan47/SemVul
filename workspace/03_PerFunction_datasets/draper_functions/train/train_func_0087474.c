xtree_refresh_depth(xtree_t* tree)
{
	if (tree->state & XTREE_STATE_DEPTHCACHED)
		return;
	tree->depth  = xtree_depth_const_node(tree, tree->root);
	tree->state |= XTREE_STATE_DEPTHCACHED;
}
