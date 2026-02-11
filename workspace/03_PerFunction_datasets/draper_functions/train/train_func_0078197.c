process_all_refs(struct send_ctx *sctx,
			    enum btrfs_compare_tree_result cmd)
{
	int ret;
	struct btrfs_root *root;
	struct btrfs_path *path;
	struct btrfs_key key;
	struct btrfs_key found_key;
	struct extent_buffer *eb;
	int slot;
	iterate_inode_ref_t cb;
	int pending_move = 0;

	path = alloc_path_for_send();
	if (!path)
		return -ENOMEM;

	if (cmd == BTRFS_COMPARE_TREE_NEW) {
		root = sctx->send_root;
		cb = __record_new_ref;
	} else if (cmd == BTRFS_COMPARE_TREE_DELETED) {
		root = sctx->parent_root;
		cb = __record_deleted_ref;
	} else {
		btrfs_err(sctx->send_root->fs_info,
				"Wrong command %d in process_all_refs", cmd);
		ret = -EINVAL;
		goto out;
	}

	key.objectid = sctx->cmp_key->objectid;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(NULL, root, &key, path, 0, 0);
	if (ret < 0)
		goto out;

	while (1) {
		eb = path->nodes[0];
		slot = path->slots[0];
		if (slot >= btrfs_header_nritems(eb)) {
			ret = btrfs_next_leaf(root, path);
			if (ret < 0)
				goto out;
			else if (ret > 0)
				break;
			continue;
		}

		btrfs_item_key_to_cpu(eb, &found_key, slot);

		if (found_key.objectid != key.objectid ||
		    (found_key.type != BTRFS_INODE_REF_KEY &&
		     found_key.type != BTRFS_INODE_EXTREF_KEY))
			break;

		ret = iterate_inode_ref(root, path, &found_key, 0, cb, sctx);
		if (ret < 0)
			goto out;

		path->slots[0]++;
	}
	btrfs_release_path(path);

	ret = process_recorded_refs(sctx, &pending_move);

	ASSERT(pending_move == 0);

out:
	btrfs_free_path(path);
	return ret;
}
