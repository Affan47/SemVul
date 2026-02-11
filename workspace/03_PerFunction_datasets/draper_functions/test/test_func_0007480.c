__ext_tree_search(struct rb_root *root, sector_t start)
{
	struct rb_node *node = root->rb_node;
	struct pnfs_block_extent *be = NULL;

	while (node) {
		be = ext_node(node);
		if (start < be->be_f_offset)
			node = node->rb_left;
		else if (start >= ext_f_end(be))
			node = node->rb_right;
		else
			return be;
	}

	if (be) {
		if (start < be->be_f_offset)
			return be;

		if (start >= ext_f_end(be))
			return ext_tree_next(be);
	}

	return NULL;
}
