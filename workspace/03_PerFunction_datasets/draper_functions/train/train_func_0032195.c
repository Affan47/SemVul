__read_block(int fd, void *buf, off_t offset, size_t count)
{
	ssize_t ret;

	ret = pread(fd, buf, count, offset);
	if (ret < 0) {
		perror("pread");
		return 1;
	} else if (!ret)
		return 1;
	else if (ret != count) {
		log_err("dedupe: short read on block\n");
		return 1;
	}

	return 0;
}
