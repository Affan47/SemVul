safe_pwrite(int fd, const void *buf, size_t count, off_t offset)
{
	while (count > 0) {
		ssize_t r = pwrite(fd, buf, count, offset);
		if (r < 0) {
			if (errno == EINTR)
				continue;
			return -errno;
		}
		count -= r;
		buf = (char *)buf + r;
		offset += r;
	}
	return 0;
}
