get_disk_info(const char *dev, size_t *blocks, size_t *bsize)
{
	uint64_t nbytes;
	int blocksz;
	int fd;

	if ((fd = open(dev, O_RDONLY)) < 0) {
		tc_log(1, "Error opening %s\n", dev);
		return -1;
	}

	if ((ioctl(fd, BLKSSZGET, &blocksz)) < 0) {
		close(fd);
		return -1;
	}

	if ((ioctl(fd, BLKGETSIZE64, &nbytes)) < 0) {
		close(fd);
		return -1;
	}

	*blocks = (size_t)(nbytes / blocksz);
	*bsize = (size_t)(blocksz);

	close(fd);
	return 0;
}
