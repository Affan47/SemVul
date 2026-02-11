chipsetready_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	char msgtype[64];

	if (sscanf(buf, "%63s", msgtype) != 1)
		return -EINVAL;

	if (!strcmp(msgtype, "CALLHOMEDISK_MOUNTED")) {
		chipset_events[0] = 1;
		return count;
	} else if (!strcmp(msgtype, "MODULES_LOADED")) {
		chipset_events[1] = 1;
		return count;
	}
	return -EINVAL;
}
