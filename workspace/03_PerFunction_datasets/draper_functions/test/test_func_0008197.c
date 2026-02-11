sysfs_get_size (struct sysfs_device * dev, unsigned long long * size)
{
	char *attr;
	int r;

	attr = sysfs_attr_get_value(dev->devpath, "size");
	if (!attr)
		return 1;

	r = sscanf(attr, "%llu\n", size);

	if (r != 1)
		return 1;

	return 0;
}
