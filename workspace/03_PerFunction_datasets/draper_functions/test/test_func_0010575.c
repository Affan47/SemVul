btrfs_release_delayed_iref(struct btrfs_delayed_node *delayed_node)
{
	struct btrfs_delayed_root *delayed_root;

	ASSERT(delayed_node->root);
	clear_bit(BTRFS_DELAYED_NODE_DEL_IREF, &delayed_node->flags);
	delayed_node->count--;

	delayed_root = delayed_node->root->fs_info->delayed_root;
	finish_one_item(delayed_root);
}
