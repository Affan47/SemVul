ext_tree_prev(struct pnfs_block_extent *be)
{
	struct rb_node *node = rb_prev(&be->be_node);
	return node ? ext_node(node) : NULL;
}
