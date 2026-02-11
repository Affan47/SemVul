backref_tree_panic(struct rb_node *rb_node, int errno, u64 bytenr)
{

	struct btrfs_fs_info *fs_info = NULL;
	struct backref_node *bnode = rb_entry(rb_node, struct backref_node,
					      rb_node);
	if (bnode->root)
		fs_info = bnode->root->fs_info;
	btrfs_panic(fs_info, errno, "Inconsistency in backref cache "
		    "found at offset %llu", bytenr);
}
