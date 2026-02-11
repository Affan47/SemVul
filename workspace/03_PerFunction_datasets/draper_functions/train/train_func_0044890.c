o2hb_region_release(struct config_item *item)
{
	int i;
	struct page *page;
	struct o2hb_region *reg = to_o2hb_region(item);

	mlog(ML_HEARTBEAT, "hb region release (%s)\n", reg->hr_dev_name);

	kfree(reg->hr_tmp_block);

	if (reg->hr_slot_data) {
		for (i = 0; i < reg->hr_num_pages; i++) {
			page = reg->hr_slot_data[i];
			if (page)
				__free_page(page);
		}
		kfree(reg->hr_slot_data);
	}

	if (reg->hr_bdev)
		blkdev_put(reg->hr_bdev, FMODE_READ|FMODE_WRITE);

	kfree(reg->hr_slots);

	kfree(reg->hr_db_regnum);
	kfree(reg->hr_db_livenodes);
	debugfs_remove(reg->hr_debug_livenodes);
	debugfs_remove(reg->hr_debug_regnum);
	debugfs_remove(reg->hr_debug_elapsed_time);
	debugfs_remove(reg->hr_debug_pinned);
	debugfs_remove(reg->hr_debug_dir);

	spin_lock(&o2hb_live_lock);
	list_del(&reg->hr_all_item);
	spin_unlock(&o2hb_live_lock);

	kfree(reg);
}
