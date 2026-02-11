befs_btree_find(struct super_block *sb, befs_data_stream * ds,
		const char *key, befs_off_t * value)
{
	struct befs_btree_node *this_node;
	befs_btree_super bt_super;
	befs_off_t node_off;
	int res;

	befs_debug(sb, "---> %s Key: %s", __func__, key);

	if (befs_bt_read_super(sb, ds, &bt_super) != BEFS_OK) {
		befs_error(sb,
			   "befs_btree_find() failed to read index superblock");
		goto error;
	}

	this_node = kmalloc(sizeof(struct befs_btree_node),
						GFP_NOFS);
	if (!this_node) {
		befs_error(sb, "befs_btree_find() failed to allocate %zu "
			   "bytes of memory", sizeof(struct befs_btree_node));
		goto error;
	}

	this_node->bh = NULL;


	node_off = bt_super.root_node_ptr;
	if (befs_bt_read_node(sb, ds, this_node, node_off) != BEFS_OK) {
		befs_error(sb, "befs_btree_find() failed to read "
			   "node at %llu", node_off);
		goto error_alloc;
	}

	while (!befs_leafnode(this_node)) {
		res = befs_find_key(sb, this_node, key, &node_off);
		if (res == BEFS_BT_NOT_FOUND)
			node_off = this_node->head.overflow;

		if (befs_bt_read_node(sb, ds, this_node, node_off) != BEFS_OK) {
			befs_error(sb, "befs_btree_find() failed to read "
				   "node at %llu", node_off);
			goto error_alloc;
		}
	}


	res = befs_find_key(sb, this_node, key, value);

	brelse(this_node->bh);
	kfree(this_node);

	if (res != BEFS_BT_MATCH) {
		befs_debug(sb, "<--- %s Key %s not found", __func__, key);
		*value = 0;
		return BEFS_BT_NOT_FOUND;
	}
	befs_debug(sb, "<--- %s Found key %s, value %llu", __func__,
		   key, *value);
	return BEFS_OK;

      error_alloc:
	kfree(this_node);
      error:
	*value = 0;
	befs_debug(sb, "<--- %s ERROR", __func__);
	return BEFS_ERR;
}
