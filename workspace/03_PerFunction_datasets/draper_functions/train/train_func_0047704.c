full_pwrite(int fd, const void *buf, size_t size, off_t offset)
{
	while (size != 0) {
		ssize_t run, res;

		if (size > SSIZE_MAX)
			run = SSIZE_MAX;
		else
			run = size;
		res = pwrite(fd, buf, run, offset);
		if (res < 0)
			return -1;
		if (res == 0) {
			errno = ENXIO;
			return -1;
		}
		buf = (const unsigned char *)buf + res;
		size -= res;
		offset += res;
	}
	return 0;
}
