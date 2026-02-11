__read(int fd, void *buf, size_t count)
{
	ssize_t len, pos = 0;

	while (count > 0) {
		len = read(fd, buf + pos, count);
		if (len <= 0)
			return len;

		count -= len;
		pos   += len;
	}

	return pos;
}
