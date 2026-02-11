radeon_hwmon_show_temp_thresh(struct device *dev,
					     struct device_attribute *attr,
					     char *buf)
{
	struct radeon_device *rdev = dev_get_drvdata(dev);
	int hyst = to_sensor_dev_attr(attr)->index;
	int temp;

	if (hyst)
		temp = rdev->pm.dpm.thermal.min_temp;
	else
		temp = rdev->pm.dpm.thermal.max_temp;

	return snprintf(buf, PAGE_SIZE, "%d\n", temp);
}
