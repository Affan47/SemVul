ocfs2_find_refcount_tree(struct ocfs2_super *osb, u64 blkno)
{
	struct rb_node *n = osb->osb_rf_lock_tree.rb_node;
	struct ocfs2_refcount_tree *tree = NULL;

	while (n) {
		tree = rb_entry(n, struct ocfs2_refcount_tree, rf_node);

		if (blkno < tree->rf_blkno)
			n = n->rb_left;
		else if (blkno > tree->rf_blkno)
			n = n->rb_right;
		else
			return tree;
	}

	return NULL;
}
