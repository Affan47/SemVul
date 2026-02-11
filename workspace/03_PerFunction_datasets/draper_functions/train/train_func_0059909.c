get_random_id(void) {
	int fd;
	unsigned int v;
	ssize_t rv = -1;
	struct timeval tv;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd >= 0) {
	        rv = xread(fd, &v, sizeof v);
		close(fd);
	}

	if (rv == sizeof v)
		return v;


	gettimeofday(&tv, NULL);
	return (unsigned int)(tv.tv_sec + (tv.tv_usec << 12) + getpid());
}
