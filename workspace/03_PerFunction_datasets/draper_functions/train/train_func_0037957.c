btrfs_find_space_cluster(struct btrfs_root *root,
			     struct btrfs_block_group_cache *block_group,
			     struct btrfs_free_cluster *cluster,
			     u64 offset, u64 bytes, u64 empty_size)
{
	struct btrfs_free_space_ctl *ctl = block_group->free_space_ctl;
	struct btrfs_free_space *entry, *tmp;
	LIST_HEAD(bitmaps);
	u64 min_bytes;
	u64 cont1_bytes;
	int ret;


	if (btrfs_test_opt(root, SSD_SPREAD)) {
		cont1_bytes = min_bytes = bytes + empty_size;
	} else if (block_group->flags & BTRFS_BLOCK_GROUP_METADATA) {
		cont1_bytes = bytes;
		min_bytes = block_group->sectorsize;
	} else {
		cont1_bytes = max(bytes, (bytes + empty_size) >> 2);
		min_bytes = block_group->sectorsize;
	}

	spin_lock(&ctl->tree_lock);


	if (ctl->free_space < bytes) {
		spin_unlock(&ctl->tree_lock);
		return -ENOSPC;
	}

	spin_lock(&cluster->lock);


	if (cluster->block_group) {
		ret = 0;
		goto out;
	}

	trace_btrfs_find_cluster(block_group, offset, bytes, empty_size,
				 min_bytes);

	ret = setup_cluster_no_bitmap(block_group, cluster, &bitmaps, offset,
				      bytes + empty_size,
				      cont1_bytes, min_bytes);
	if (ret)
		ret = setup_cluster_bitmap(block_group, cluster, &bitmaps,
					   offset, bytes + empty_size,
					   cont1_bytes, min_bytes);


	list_for_each_entry_safe(entry, tmp, &bitmaps, list)
		list_del_init(&entry->list);

	if (!ret) {
		atomic_inc(&block_group->count);
		list_add_tail(&cluster->block_group_list,
			      &block_group->cluster_list);
		cluster->block_group = block_group;
	} else {
		trace_btrfs_failed_cluster_setup(block_group);
	}
out:
	spin_unlock(&cluster->lock);
	spin_unlock(&ctl->tree_lock);

	return ret;
}
