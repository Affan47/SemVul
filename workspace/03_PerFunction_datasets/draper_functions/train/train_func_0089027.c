brd_alloc(int i)
{
	struct brd_device *brd;
	struct gendisk *disk;

	brd = kzalloc(sizeof(*brd), GFP_KERNEL);
	if (!brd)
		goto out;
	brd->brd_number		= i;
	spin_lock_init(&brd->brd_lock);
	INIT_RADIX_TREE(&brd->brd_pages, GFP_ATOMIC);

	brd->brd_queue = blk_alloc_queue(GFP_KERNEL);
	if (!brd->brd_queue)
		goto out_free_dev;

	blk_queue_make_request(brd->brd_queue, brd_make_request);
	blk_queue_max_hw_sectors(brd->brd_queue, 1024);
	blk_queue_bounce_limit(brd->brd_queue, BLK_BOUNCE_ANY);


	blk_queue_physical_block_size(brd->brd_queue, PAGE_SIZE);

	brd->brd_queue->limits.discard_granularity = PAGE_SIZE;
	blk_queue_max_discard_sectors(brd->brd_queue, UINT_MAX);
	brd->brd_queue->limits.discard_zeroes_data = 1;
	queue_flag_set_unlocked(QUEUE_FLAG_DISCARD, brd->brd_queue);

	disk = brd->brd_disk = alloc_disk(max_part);
	if (!disk)
		goto out_free_queue;
	disk->major		= RAMDISK_MAJOR;
	disk->first_minor	= i * max_part;
	disk->fops		= &brd_fops;
	disk->private_data	= brd;
	disk->queue		= brd->brd_queue;
	disk->flags		= GENHD_FL_EXT_DEVT;
	sprintf(disk->disk_name, "ram%d", i);
	set_capacity(disk, rd_size * 2);

	return brd;

out_free_queue:
	blk_cleanup_queue(brd->brd_queue);
out_free_dev:
	kfree(brd);
out:
	return NULL;
}
