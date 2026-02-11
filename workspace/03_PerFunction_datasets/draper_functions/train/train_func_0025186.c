f2fs_get_device_info(struct f2fs_configuration *c)
{
	int32_t fd = 0;
	int32_t sector_size;
	struct stat stat_buf;
	struct hd_geometry geom;

	fd = open(c->device_name, O_RDWR);
	if (fd < 0) {
		MSG(0, "\tError: Failed to open the device!\n");
		return -1;
	}
	c->fd = fd;

	if (fstat(fd, &stat_buf) < 0 ) {
		MSG(0, "\tError: Failed to get the device stat!\n");
		return -1;
	}

	if (S_ISREG(stat_buf.st_mode)) {
		c->total_sectors = stat_buf.st_size / c->sector_size;
	} else if (S_ISBLK(stat_buf.st_mode)) {
		if (ioctl(fd, BLKSSZGET, &sector_size) < 0) {
			MSG(0, "\tError: Using the default sector size\n");
		} else {
			if (c->sector_size < sector_size) {
				MSG(0, "\tError: Cannot set the sector size to:"
					" %d as the device does not support"
					"\nSetting the sector size to : %d\n",
					c->sector_size, sector_size);
				c->sector_size = sector_size;
				c->sectors_per_blk = PAGE_SIZE / sector_size;
			}
		}

		if (ioctl(fd, BLKGETSIZE, &c->total_sectors) < 0) {
			MSG(0, "\tError: Cannot get the device size\n");
			return -1;
		}

		if (ioctl(fd, HDIO_GETGEO, &geom) < 0)
			c->start_sector = 0;
		else
			c->start_sector = geom.start;
	} else {
		MSG(0, "\tError: Volume type is not supported!!!\n");
		return -1;
	}

	MSG(0, "Info: sector size = %u\n", c->sector_size);
	MSG(0, "Info: total sectors = %"PRIu64" (in 512bytes)\n",
					c->total_sectors);
	if (c->total_sectors <
			(F2FS_MIN_VOLUME_SIZE / DEFAULT_SECTOR_SIZE)) {
		MSG(0, "Error: Min volume size supported is %d\n",
				F2FS_MIN_VOLUME_SIZE);
		return -1;
	}

	return 0;
}
