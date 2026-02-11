btrfs_next_delayed_node(
						struct btrfs_delayed_node *node)
{
	struct btrfs_delayed_root *delayed_root;
	struct list_head *p;
	struct btrfs_delayed_node *next = NULL;

	delayed_root = node->root->fs_info->delayed_root;
	spin_lock(&delayed_root->lock);
	if (!test_bit(BTRFS_DELAYED_NODE_IN_LIST, &node->flags)) {

		if (list_empty(&delayed_root->node_list))
			goto out;
		p = delayed_root->node_list.next;
	} else if (list_is_last(&node->n_list, &delayed_root->node_list))
		goto out;
	else
		p = node->n_list.next;

	next = list_entry(p, struct btrfs_delayed_node, n_list);
	atomic_inc(&next->refs);
out:
	spin_unlock(&delayed_root->lock);

	return next;
}
