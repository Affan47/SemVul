proxy_gets(int fd, char *buf, size_t len)
{
	int i = 0;
	int ret;

	if (len < 2)
		return -EINVAL;

	while ( (ret = read(fd, buf + i, 1)) == 1) {
		if (buf[i] == '\n') {
			buf[i] = 0;
			if (i && buf[i-1] == '\r') {
				buf[i-1] = 0;
				i--;
			}
			return i;
		}
		i++;

		if (i >= len - 1) {
			buf[i] = 0;
			return i;
		}
	}
	if (ret < 0)
		ret = -errno;

	buf[i] = 0;
	return i ?: ret;
}
