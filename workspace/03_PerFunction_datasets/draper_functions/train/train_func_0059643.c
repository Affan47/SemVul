_dev_get_size_dev(const struct device *dev, uint64_t *size)
{
	int fd;
	const char *name = dev_name(dev);

	if ((fd = open(name, O_RDONLY)) < 0) {
		log_sys_error("open", name);
		return 0;
	}

	if (ioctl(fd, BLKGETSIZE64, size) < 0) {
		log_sys_error("ioctl BLKGETSIZE64", name);
		if (close(fd))
			log_sys_error("close", name);
		return 0;
	}

	*size >>= BLKSIZE_SHIFT;
	if (close(fd))
		log_sys_error("close", name);

	log_very_verbose("%s: size is %" PRIu64 " sectors", name, *size);

	return 1;
}
