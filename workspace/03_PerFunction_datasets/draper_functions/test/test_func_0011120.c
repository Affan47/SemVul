sysfs_scsi_path_contains(struct sysfs_cxt *cxt, const char *pattern)
{
	char path[PATH_MAX], linkc[PATH_MAX];
	struct stat st;
	ssize_t len;

	if (!sysfs_scsi_attribute_path(cxt, path, sizeof(path), NULL))
		return 0;

	if (stat(path, &st) != 0)
		return 0;

	len = readlink(path, linkc, sizeof(linkc) - 1);
	if (len < 0)
		return 0;

	linkc[len] = '\0';
	return strstr(linkc, pattern) != NULL;
}
