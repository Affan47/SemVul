show_in(struct device *dev, struct device_attribute *devattr, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct menf21bmc_hwmon *drv_data = menf21bmc_hwmon_update(dev);

	if (IS_ERR(drv_data))
		return PTR_ERR(drv_data);

	return sprintf(buf, "%d\n", drv_data->in_val[attr->index]);
}
