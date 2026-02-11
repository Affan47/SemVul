get_rp_filter()
{
	FILE *f;
	int value = -EINVAL, tmp;

	f = fopen("/proc/sys/net/ipv4/conf/all/rp_filter", "r");

	if (f != NULL) {
		if (fscanf(f, "%d", &tmp) == 1)
			value = tmp;
		fclose(f);
	}

	return value;
}
