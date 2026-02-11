common_sysfs_pathinfo (struct path * pp, struct sysfs_device *dev)
{
	char *attr;

	attr = sysfs_attr_get_value(dev->devpath, "dev");
	if (!attr) {
		condlog(3, "%s: no 'dev' attribute in sysfs", pp->dev);
		return 1;
	}
	strlcpy(pp->dev_t, attr, BLK_DEV_SIZE);

	condlog(3, "%s: dev_t = %s", pp->dev, pp->dev_t);

	if (sysfs_get_size(dev, &pp->size))
		return 1;

	condlog(3, "%s: size = %llu", pp->dev, pp->size);

	return 0;
}
