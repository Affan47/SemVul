__btrfs_lookup_delayed_item(
				struct rb_root *root,
				struct btrfs_key *key,
				struct btrfs_delayed_item **prev,
				struct btrfs_delayed_item **next)
{
	struct rb_node *node, *prev_node = NULL;
	struct btrfs_delayed_item *delayed_item = NULL;
	int ret = 0;

	node = root->rb_node;

	while (node) {
		delayed_item = rb_entry(node, struct btrfs_delayed_item,
					rb_node);
		prev_node = node;
		ret = btrfs_comp_cpu_keys(&delayed_item->key, key);
		if (ret < 0)
			node = node->rb_right;
		else if (ret > 0)
			node = node->rb_left;
		else
			return delayed_item;
	}

	if (prev) {
		if (!prev_node)
			*prev = NULL;
		else if (ret < 0)
			*prev = delayed_item;
		else if ((node = rb_prev(prev_node)) != NULL) {
			*prev = rb_entry(node, struct btrfs_delayed_item,
					 rb_node);
		} else
			*prev = NULL;
	}

	if (next) {
		if (!prev_node)
			*next = NULL;
		else if (ret > 0)
			*next = delayed_item;
		else if ((node = rb_next(prev_node)) != NULL) {
			*next = rb_entry(node, struct btrfs_delayed_item,
					 rb_node);
		} else
			*next = NULL;
	}
	return NULL;
}
