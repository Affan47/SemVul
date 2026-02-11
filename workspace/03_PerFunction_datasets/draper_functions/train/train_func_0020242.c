mapping_tree_init(struct mapping_tree *tree)
{
	tree->rb_root = RB_ROOT;
	spin_lock_init(&tree->lock);
}
