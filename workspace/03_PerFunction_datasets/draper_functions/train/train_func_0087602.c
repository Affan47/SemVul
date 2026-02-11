__btrfs_release_delayed_node(
				struct btrfs_delayed_node *delayed_node,
				int mod)
{
	struct btrfs_delayed_root *delayed_root;

	if (!delayed_node)
		return;

	delayed_root = delayed_node->root->fs_info->delayed_root;

	mutex_lock(&delayed_node->mutex);
	if (delayed_node->count)
		btrfs_queue_delayed_node(delayed_root, delayed_node, mod);
	else
		btrfs_dequeue_delayed_node(delayed_root, delayed_node);
	mutex_unlock(&delayed_node->mutex);

	if (atomic_dec_and_test(&delayed_node->refs)) {
		bool free = false;
		struct btrfs_root *root = delayed_node->root;
		spin_lock(&root->inode_lock);
		if (atomic_read(&delayed_node->refs) == 0) {
			radix_tree_delete(&root->delayed_nodes_tree,
					  delayed_node->inode_id);
			free = true;
		}
		spin_unlock(&root->inode_lock);
		if (free)
			kmem_cache_free(delayed_node_cache, delayed_node);
	}
}
