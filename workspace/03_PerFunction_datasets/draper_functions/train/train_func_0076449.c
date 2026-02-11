pd_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct pd_unit *disk = bdev->bd_disk->private_data;

	if (disk->alt_geom) {
		geo->heads = PD_LOG_HEADS;
		geo->sectors = PD_LOG_SECTS;
		geo->cylinders = disk->capacity / (geo->heads * geo->sectors);
	} else {
		geo->heads = disk->heads;
		geo->sectors = disk->sectors;
		geo->cylinders = disk->cylinders;
	}

	return 0;
}
