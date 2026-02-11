btrfs_first_prepared_delayed_node(
					struct btrfs_delayed_root *delayed_root)
{
	struct list_head *p;
	struct btrfs_delayed_node *node = NULL;

	spin_lock(&delayed_root->lock);
	if (list_empty(&delayed_root->prepare_list))
		goto out;

	p = delayed_root->prepare_list.next;
	list_del_init(p);
	node = list_entry(p, struct btrfs_delayed_node, p_list);
	atomic_inc(&node->refs);
out:
	spin_unlock(&delayed_root->lock);

	return node;
}
