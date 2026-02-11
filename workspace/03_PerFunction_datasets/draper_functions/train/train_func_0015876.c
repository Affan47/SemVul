sensors_add_hwmon_device_compat(const char *path,
					   const char *dev_name)
{
	int err;

	err = sensors_read_one_sysfs_chip(path, dev_name, path);
	if (err < 0)
		return err;
	return 0;
}
