set_timespec(struct timespec *timeout, const char *str)
{
	char *end = NULL;
	unsigned long ulong;

	if (*str == '\0' || strchr(str, '-'))
		return -1;

	errno = 0;
	ulong = strtoul(str, &end, 0);
	if (errno != 0)
		return -1;
	if (*end == '\0' || strcmp(end, "s") == 0) {
		timeout->tv_sec = ulong;
		timeout->tv_nsec = 0;
	} else if (strcmp(end, "ms") == 0) {
		timeout->tv_sec = ulong / 1000;
		timeout->tv_nsec = (ulong % 1000) * 1000;
	} else if (strcmp(end, "us") == 0) {
		timeout->tv_sec = ulong / 1000000;
		timeout->tv_nsec = (ulong % 1000000) * 1000;
	} else {
		return -1;
	}

	return 0;
}
