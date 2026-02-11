dm_format_dev(char *buf, int bufsize, uint32_t dev_major,
		  uint32_t dev_minor)
{
	int r;

	if (bufsize < 8)
		return 0;

	r = snprintf(buf, (size_t) bufsize, "%u:%u", dev_major, dev_minor);
	if (r < 0 || r > bufsize - 1)
		return 0;

	return 1;
}
