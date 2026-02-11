btrfs_recover_balance(struct btrfs_fs_info *fs_info)
{
	struct btrfs_balance_control *bctl;
	struct btrfs_balance_item *item;
	struct btrfs_disk_balance_args disk_bargs;
	struct btrfs_path *path;
	struct extent_buffer *leaf;
	struct btrfs_key key;
	int ret;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	key.objectid = BTRFS_BALANCE_OBJECTID;
	key.type = BTRFS_BALANCE_ITEM_KEY;
	key.offset = 0;

	ret = btrfs_search_slot(NULL, fs_info->tree_root, &key, path, 0, 0);
	if (ret < 0)
		goto out;
	if (ret > 0) {
		ret = 0;
		goto out;
	}

	bctl = kzalloc(sizeof(*bctl), GFP_NOFS);
	if (!bctl) {
		ret = -ENOMEM;
		goto out;
	}

	leaf = path->nodes[0];
	item = btrfs_item_ptr(leaf, path->slots[0], struct btrfs_balance_item);

	bctl->fs_info = fs_info;
	bctl->flags = btrfs_balance_flags(leaf, item);
	bctl->flags |= BTRFS_BALANCE_RESUME;

	btrfs_balance_data(leaf, item, &disk_bargs);
	btrfs_disk_balance_args_to_cpu(&bctl->data, &disk_bargs);
	btrfs_balance_meta(leaf, item, &disk_bargs);
	btrfs_disk_balance_args_to_cpu(&bctl->meta, &disk_bargs);
	btrfs_balance_sys(leaf, item, &disk_bargs);
	btrfs_disk_balance_args_to_cpu(&bctl->sys, &disk_bargs);

	WARN_ON(atomic_xchg(&fs_info->mutually_exclusive_operation_running, 1));

	mutex_lock(&fs_info->volume_mutex);
	mutex_lock(&fs_info->balance_mutex);

	set_balance_control(bctl);

	mutex_unlock(&fs_info->balance_mutex);
	mutex_unlock(&fs_info->volume_mutex);
out:
	btrfs_free_path(path);
	return ret;
}
