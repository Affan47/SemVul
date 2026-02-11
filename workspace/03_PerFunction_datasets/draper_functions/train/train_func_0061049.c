Linux_GetSysDrvAttr(const char *in_dev, const char *attr) {
	char devlink[256];
	struct stat buf;

	snprintf(devlink, 256, "/sys/class/net/%s/%s", in_dev, attr);

	if (stat(devlink, &buf) != 0)
		return 0;

	return 1;
}
