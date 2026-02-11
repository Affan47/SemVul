sysfs_get_dev (struct sysfs_device * dev, char * buff, size_t len)
{
	char *attr;

	attr = sysfs_attr_get_value(dev->devpath, "dev");
	if (!attr) {
		condlog(3, "%s: no 'dev' attribute in sysfs", dev->kernel);
		return 1;
	}
	if (strlcpy(buff, attr, len) != strlen(attr)) {
		condlog(3, "%s: overflow in 'dev' attribute", dev->kernel);
		return 2;
	}
	return 0;
}
