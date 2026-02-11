secure_erase(const char *dev, size_t bytes, size_t blksz)
{
	size_t erased = 0;
	int fd_rand, fd;
	char buf[ERASE_BUFFER_SIZE];
	ssize_t r, w;
	size_t sz;

	if (blksz > MAX_BLKSZ) {
		tc_log(1, "blksz > MAX_BLKSZ\n");
		return -1;
	}

	if ((fd_rand = open("/dev/urandom", O_RDONLY)) < 0) {
		tc_log(1, "Error opening /dev/urandom\n");
		return -1;
	}

	if ((fd = open(dev, O_WRONLY)) < 0) {
		close(fd_rand);
		tc_log(1, "Error opening %s\n", dev);
		return -1;
	}

	summary_fn = secure_erase_summary;
	secure_erase_total_bytes = bytes;

	sz = ERASE_BUFFER_SIZE;
	while (erased < bytes) {
		secure_erase_erased_bytes = erased;

		if ((bytes - erased) <= ERASE_BUFFER_SIZE)
			sz = blksz;

		if ((r = read(fd_rand, buf, sz)) < 0) {
			tc_log(1, "Error reading from /dev/urandom\n");
			close(fd);
			close(fd_rand);
			summary_fn = NULL;
			return -1;
		}

		if (r < (ssize_t)blksz)
			continue;

		if ((w = write(fd, buf, r)) < 0) {
			tc_log(1, "Error writing to %s\n", dev);
			close(fd);
			close(fd_rand);
			summary_fn = NULL;
			return -1;
		}

		erased += (size_t)w;
	}

	close(fd);
	close(fd_rand);

	summary_fn = NULL;

	return 0;
}
