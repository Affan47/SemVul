_read_uint64(const char *sysfs_path, uint64_t *value)
{
	char tmp[64] = {0};
	int fd, r;

	if ((fd = open(sysfs_path, O_RDONLY)) < 0)
		return 0;
	r = read(fd, tmp, sizeof(tmp));
	close(fd);

	if (r <= 0)
		return 0;

        if (sscanf(tmp, "%" PRIu64, value) != 1)
		return 0;

	return 1;
}
