btrfs_inode_delayed_dir_index_count(struct inode *inode)
{
	struct btrfs_delayed_node *delayed_node = btrfs_get_delayed_node(inode);

	if (!delayed_node)
		return -ENOENT;


	if (!delayed_node->index_cnt) {
		btrfs_release_delayed_node(delayed_node);
		return -EINVAL;
	}

	BTRFS_I(inode)->index_cnt = delayed_node->index_cnt;
	btrfs_release_delayed_node(delayed_node);
	return 0;
}
