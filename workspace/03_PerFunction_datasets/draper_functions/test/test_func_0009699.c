mem_fmt(char *buf, int size, unsigned long hsize)
{
	if (hsize >= (1UL << 30))
		snprintf(buf, size, "%luGB", hsize >> 30);
	else if (hsize >= (1UL << 20))
		snprintf(buf, size, "%luMB", hsize >> 20);
	else
		snprintf(buf, size, "%luKB", hsize >> 10);
	return buf;
}
