select_reloc_root(struct btrfs_trans_handle *trans,
				     struct reloc_control *rc,
				     struct backref_node *node,
				     struct backref_edge *edges[])
{
	struct backref_node *next;
	struct btrfs_root *root;
	int index = 0;

	next = node;
	while (1) {
		cond_resched();
		next = walk_up_backref(next, edges, &index);
		root = next->root;
		BUG_ON(!root);
		BUG_ON(!test_bit(BTRFS_ROOT_REF_COWS, &root->state));

		if (root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID) {
			record_reloc_root_in_trans(trans, root);
			break;
		}

		btrfs_record_root_in_trans(trans, root);
		root = root->reloc_root;

		if (next->new_bytenr != root->node->start) {
			BUG_ON(next->new_bytenr);
			BUG_ON(!list_empty(&next->list));
			next->new_bytenr = root->node->start;
			next->root = root;
			list_add_tail(&next->list,
				      &rc->backref_cache.changed);
			__mark_block_processed(rc, next);
			break;
		}

		WARN_ON(1);
		root = NULL;
		next = walk_down_backref(edges, &index);
		if (!next || next->level <= node->level)
			break;
	}
	if (!root)
		return NULL;

	next = node;

	while (1) {
		rc->backref_cache.path[next->level] = next;
		if (--index < 0)
			break;
		next = edges[index]->node[UPPER];
	}
	return root;
}
