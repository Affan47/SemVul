show_status(struct device *dev,
	struct device_attribute *devattr, char *buf)
{
	int nr = to_sensor_dev_attr_2(devattr)->nr;
	int mask = to_sensor_dev_attr_2(devattr)->index;
	struct tmp401_data *data = tmp401_update_device(dev);

	if (IS_ERR(data))
		return PTR_ERR(data);

	return sprintf(buf, "%d\n", !!(data->status[nr] & mask));
}
