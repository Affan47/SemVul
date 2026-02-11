sr_block_open(struct block_device *bdev, fmode_t mode)
{
	struct scsi_cd *cd;
	int ret = -ENXIO;

	mutex_lock(&sr_mutex);
	cd = scsi_cd_get(bdev->bd_disk);
	if (cd) {
		ret = cdrom_open(&cd->cdi, bdev, mode);
		if (ret)
			scsi_cd_put(cd);
	}
	mutex_unlock(&sr_mutex);
	return ret;
}
