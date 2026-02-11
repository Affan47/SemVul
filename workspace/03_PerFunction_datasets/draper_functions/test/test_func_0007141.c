device_block_size(struct device *device)
{
	struct stat st;
	int fd, bsize = 0, r = -EINVAL;

	if (!device)
		return 0;

	fd = open(device->path, O_RDONLY);
	if(fd < 0)
		return -EINVAL;

	if (fstat(fd, &st) < 0)
		goto out;

	if (S_ISREG(st.st_mode) || device->file_path) {
		r = (int)crypt_getpagesize();
		goto out;
	}

	if (ioctl(fd, BLKSSZGET, &bsize) >= 0)
		r = bsize;
out:
	close(fd);
	return r;
}
