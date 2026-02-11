replay_dir_deletes(struct btrfs_trans_handle *trans,
				       struct btrfs_root *root,
				       struct btrfs_root *log,
				       struct btrfs_path *path,
				       u64 dirid, int del_all)
{
	u64 range_start;
	u64 range_end;
	int key_type = BTRFS_DIR_LOG_ITEM_KEY;
	int ret = 0;
	struct btrfs_key dir_key;
	struct btrfs_key found_key;
	struct btrfs_path *log_path;
	struct inode *dir;

	dir_key.objectid = dirid;
	dir_key.type = BTRFS_DIR_ITEM_KEY;
	log_path = btrfs_alloc_path();
	if (!log_path)
		return -ENOMEM;

	dir = read_one_inode(root, dirid);


	if (!dir) {
		btrfs_free_path(log_path);
		return 0;
	}
again:
	range_start = 0;
	range_end = 0;
	while (1) {
		if (del_all)
			range_end = (u64)-1;
		else {
			ret = find_dir_range(log, path, dirid, key_type,
					     &range_start, &range_end);
			if (ret != 0)
				break;
		}

		dir_key.offset = range_start;
		while (1) {
			int nritems;
			ret = btrfs_search_slot(NULL, root, &dir_key, path,
						0, 0);
			if (ret < 0)
				goto out;

			nritems = btrfs_header_nritems(path->nodes[0]);
			if (path->slots[0] >= nritems) {
				ret = btrfs_next_leaf(root, path);
				if (ret)
					break;
			}
			btrfs_item_key_to_cpu(path->nodes[0], &found_key,
					      path->slots[0]);
			if (found_key.objectid != dirid ||
			    found_key.type != dir_key.type)
				goto next_type;

			if (found_key.offset > range_end)
				break;

			ret = check_item_in_log(trans, root, log, path,
						log_path, dir,
						&found_key);
			if (ret)
				goto out;
			if (found_key.offset == (u64)-1)
				break;
			dir_key.offset = found_key.offset + 1;
		}
		btrfs_release_path(path);
		if (range_end == (u64)-1)
			break;
		range_start = range_end + 1;
	}

next_type:
	ret = 0;
	if (key_type == BTRFS_DIR_LOG_ITEM_KEY) {
		key_type = BTRFS_DIR_LOG_INDEX_KEY;
		dir_key.type = BTRFS_DIR_INDEX_KEY;
		btrfs_release_path(path);
		goto again;
	}
out:
	btrfs_release_path(path);
	btrfs_free_path(log_path);
	iput(dir);
	return ret;
}
