ocfs2_erase_refcount_tree_from_list_no_lock(struct ocfs2_super *osb,
					struct ocfs2_refcount_tree *tree)
{
	rb_erase(&tree->rf_node, &osb->osb_rf_lock_tree);
	if (osb->osb_ref_tree_lru && osb->osb_ref_tree_lru == tree)
		osb->osb_ref_tree_lru = NULL;
}
