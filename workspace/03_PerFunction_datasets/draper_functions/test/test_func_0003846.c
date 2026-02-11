btt_blk_init(struct btt *btt)
{
	struct nd_btt *nd_btt = btt->nd_btt;
	struct nd_namespace_common *ndns = nd_btt->ndns;


	btt->btt_queue = blk_alloc_queue(GFP_KERNEL);
	if (!btt->btt_queue)
		return -ENOMEM;

	btt->btt_disk = alloc_disk(0);
	if (!btt->btt_disk) {
		blk_cleanup_queue(btt->btt_queue);
		return -ENOMEM;
	}

	nvdimm_namespace_disk_name(ndns, btt->btt_disk->disk_name);
	btt->btt_disk->driverfs_dev = &btt->nd_btt->dev;
	btt->btt_disk->major = btt_major;
	btt->btt_disk->first_minor = 0;
	btt->btt_disk->fops = &btt_fops;
	btt->btt_disk->private_data = btt;
	btt->btt_disk->queue = btt->btt_queue;
	btt->btt_disk->flags = GENHD_FL_EXT_DEVT;

	blk_queue_make_request(btt->btt_queue, btt_make_request);
	blk_queue_logical_block_size(btt->btt_queue, btt->sector_size);
	blk_queue_max_hw_sectors(btt->btt_queue, UINT_MAX);
	blk_queue_bounce_limit(btt->btt_queue, BLK_BOUNCE_ANY);
	queue_flag_set_unlocked(QUEUE_FLAG_NONROT, btt->btt_queue);
	btt->btt_queue->queuedata = btt;

	set_capacity(btt->btt_disk, 0);
	add_disk(btt->btt_disk);
	if (btt_meta_size(btt)) {
		int rc = nd_integrity_init(btt->btt_disk, btt_meta_size(btt));

		if (rc) {
			del_gendisk(btt->btt_disk);
			put_disk(btt->btt_disk);
			blk_cleanup_queue(btt->btt_queue);
			return rc;
		}
	}
	set_capacity(btt->btt_disk, btt->nlba * btt->sector_size >> 9);
	revalidate_disk(btt->btt_disk);

	return 0;
}
