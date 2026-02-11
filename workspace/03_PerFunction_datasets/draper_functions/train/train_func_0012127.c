update_space_info(struct btrfs_fs_info *info, u64 flags,
			     u64 total_bytes, u64 bytes_used,
			     struct btrfs_space_info **space_info)
{
	struct btrfs_space_info *found;
	int i;
	int factor;
	int ret;

	if (flags & (BTRFS_BLOCK_GROUP_DUP | BTRFS_BLOCK_GROUP_RAID1 |
		     BTRFS_BLOCK_GROUP_RAID10))
		factor = 2;
	else
		factor = 1;

	found = __find_space_info(info, flags);
	if (found) {
		spin_lock(&found->lock);
		found->total_bytes += total_bytes;
		found->disk_total += total_bytes * factor;
		found->bytes_used += bytes_used;
		found->disk_used += bytes_used * factor;
		if (total_bytes > 0)
			found->full = 0;
		spin_unlock(&found->lock);
		*space_info = found;
		return 0;
	}
	found = kzalloc(sizeof(*found), GFP_NOFS);
	if (!found)
		return -ENOMEM;

	ret = percpu_counter_init(&found->total_bytes_pinned, 0, GFP_KERNEL);
	if (ret) {
		kfree(found);
		return ret;
	}

	for (i = 0; i < BTRFS_NR_RAID_TYPES; i++)
		INIT_LIST_HEAD(&found->block_groups[i]);
	init_rwsem(&found->groups_sem);
	spin_lock_init(&found->lock);
	found->flags = flags & BTRFS_BLOCK_GROUP_TYPE_MASK;
	found->total_bytes = total_bytes;
	found->disk_total = total_bytes * factor;
	found->bytes_used = bytes_used;
	found->disk_used = bytes_used * factor;
	found->bytes_pinned = 0;
	found->bytes_reserved = 0;
	found->bytes_readonly = 0;
	found->bytes_may_use = 0;
	found->full = 0;
	found->max_extent_size = 0;
	found->force_alloc = CHUNK_ALLOC_NO_FORCE;
	found->chunk_alloc = 0;
	found->flush = 0;
	init_waitqueue_head(&found->wait);
	INIT_LIST_HEAD(&found->ro_bgs);

	ret = kobject_init_and_add(&found->kobj, &space_info_ktype,
				    info->space_info_kobj, "%s",
				    alloc_name(found->flags));
	if (ret) {
		percpu_counter_destroy(&found->total_bytes_pinned);
		kfree(found);
		return ret;
	}

	*space_info = found;
	list_add_rcu(&found->list, &info->space_info);
	if (flags & BTRFS_BLOCK_GROUP_DATA)
		info->data_sinfo = found;

	return ret;
}
