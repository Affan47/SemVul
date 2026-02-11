sysfs_count_partitions(struct sysfs_cxt *cxt, const char *devname)
{
	DIR *dir;
	struct dirent *d;
	int r = 0;

	if (!(dir = sysfs_opendir(cxt, NULL)))
		return 0;

	while ((d = xreaddir(dir))) {
		if (sysfs_is_partition_dirent(dir, d, devname))
			r++;
	}

	closedir(dir);
	return r;
}
