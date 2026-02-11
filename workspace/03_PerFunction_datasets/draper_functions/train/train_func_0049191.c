dm_blk_ioctl(struct block_device *bdev, fmode_t mode,
			unsigned int cmd, unsigned long arg)
{
	struct mapped_device *md = bdev->bd_disk->private_data;
	struct dm_target *tgt;
	struct block_device *tgt_bdev = NULL;
	int srcu_idx, r;

	r = dm_get_live_table_for_ioctl(md, &tgt, &tgt_bdev, &mode, &srcu_idx);
	if (r < 0)
		return r;

	if (r > 0) {


		r = scsi_verify_blk_ioctl(NULL, cmd);
		if (r)
			goto out;
	}

	r =  __blkdev_driver_ioctl(tgt_bdev, mode, cmd, arg);
out:
	dm_put_live_table(md, srcu_idx);
	return r;
}
