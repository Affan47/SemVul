sensors_read_sysfs_chips(void)
{
	int ret;

	ret = sysfs_foreach_classdev("hwmon", sensors_add_hwmon_device);
	if (ret == ENOENT) {

		return sensors_read_sysfs_chips_compat();
	}

	if (ret > 0)
		ret = -SENSORS_ERR_KERNEL;
	return ret;
}
