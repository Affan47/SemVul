reada_start_machine_dev(struct btrfs_fs_info *fs_info,
				   struct btrfs_device *dev)
{
	struct reada_extent *re = NULL;
	int mirror_num = 0;
	struct extent_buffer *eb = NULL;
	u64 logical;
	int ret;
	int i;
	int need_kick = 0;

	spin_lock(&fs_info->reada_lock);
	if (dev->reada_curr_zone == NULL) {
		ret = reada_pick_zone(dev);
		if (!ret) {
			spin_unlock(&fs_info->reada_lock);
			return 0;
		}
	}


	ret = radix_tree_gang_lookup(&dev->reada_extents, (void **)&re,
				     dev->reada_next >> PAGE_CACHE_SHIFT, 1);
	if (ret == 0 || re->logical >= dev->reada_curr_zone->end) {
		ret = reada_pick_zone(dev);
		if (!ret) {
			spin_unlock(&fs_info->reada_lock);
			return 0;
		}
		re = NULL;
		ret = radix_tree_gang_lookup(&dev->reada_extents, (void **)&re,
					dev->reada_next >> PAGE_CACHE_SHIFT, 1);
	}
	if (ret == 0) {
		spin_unlock(&fs_info->reada_lock);
		return 0;
	}
	dev->reada_next = re->logical + fs_info->tree_root->nodesize;
	re->refcnt++;

	spin_unlock(&fs_info->reada_lock);


	for (i = 0; i < re->nzones; ++i) {
		if (re->zones[i]->device == dev) {
			mirror_num = i + 1;
			break;
		}
	}
	logical = re->logical;

	spin_lock(&re->lock);
	if (re->scheduled_for == NULL) {
		re->scheduled_for = dev;
		need_kick = 1;
	}
	spin_unlock(&re->lock);

	reada_extent_put(fs_info, re);

	if (!need_kick)
		return 0;

	atomic_inc(&dev->reada_in_flight);
	ret = reada_tree_block_flagged(fs_info->extent_root, logical,
			mirror_num, &eb);
	if (ret)
		__readahead_hook(fs_info->extent_root, NULL, logical, ret);
	else if (eb)
		__readahead_hook(fs_info->extent_root, eb, eb->start, ret);

	if (eb)
		free_extent_buffer(eb);

	return 1;

}
