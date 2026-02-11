sysfs_devno_has_attribute(dev_t devno, const char *attr)
{
	char path[PATH_MAX];
	struct stat info;

	if (!sysfs_devno_attribute_path(devno, path, sizeof(path), attr))
		return 0;
	if (stat(path, &info) == 0)
		return 1;
	return 0;
}
