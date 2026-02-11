extent_io_tree_init(struct extent_io_tree *tree,
			 struct address_space *mapping)
{
	tree->state = RB_ROOT;
	tree->ops = NULL;
	tree->dirty_bytes = 0;
	spin_lock_init(&tree->lock);
	tree->mapping = mapping;
}
