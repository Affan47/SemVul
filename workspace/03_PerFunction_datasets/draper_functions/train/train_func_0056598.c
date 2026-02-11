bytes_per_sec(char *buf, double v)
{
	const char *order[] = {
		"",
		"KiB",
		"MiB",
		"GiB",
		"TiB",
		"PiB",
		NULL,
	}, **o = order;

	while (v > 1024 && o[1]) {
		v /= 1024;
		o++;
	}
	sprintf(buf, "%.1f%s/s", v, *o);
	return buf;
}
