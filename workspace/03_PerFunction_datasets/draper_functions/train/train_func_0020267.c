vreadfile(const char *pfx, const char *fn, ssize_t *sz)
{
	int fd, err;
	char *r;
	char fnb[PATH_MAX + 1];

	if (fn[0] == '/')
		fd = open(fn, O_RDONLY);
	else if (pfx != NULL) {
		bprintf(fnb, "/%s/%s", pfx, fn);
		fd = open(fnb, O_RDONLY);
	} else
		fd = open(fn, O_RDONLY);
	if (fd < 0)
		return (NULL);
	r = vreadfd(fd, sz);
	err = errno;
	AZ(close(fd));
	errno = err;
	return (r);
}
