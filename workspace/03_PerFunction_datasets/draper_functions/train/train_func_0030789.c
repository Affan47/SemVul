open(const char *path, int flags, ...)
{
	int (*old_open)(const char *, int, ...);
	int fd;
	va_list ap;

	old_open = dlsym(RTLD_NEXT, "open");
	if (in_test && strcmp(path, "/proc/mounts") == 0)
		return tmp_mounts_fd;
	va_start(ap, flags);
	fd = (old_open)(path, flags, va_arg(ap, mode_t));
	va_end(ap);
	return fd;
}
