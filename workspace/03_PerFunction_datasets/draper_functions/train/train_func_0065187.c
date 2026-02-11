sysfs_scsi_has_attribute(struct sysfs_cxt *cxt, const char *attr)
{
	char path[PATH_MAX];
	struct stat st;

	if (!sysfs_scsi_attribute_path(cxt, path, sizeof(path), attr))
		return 0;

	return stat(path, &st) == 0;
}
