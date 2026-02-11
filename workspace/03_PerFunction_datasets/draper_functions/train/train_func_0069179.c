show_temp_min(struct device *dev,
			     struct device_attribute *devattr,
			     char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct adt7462_data *data = adt7462_update_device(dev);

	if (!temp_enabled(data, attr->index))
		return sprintf(buf, "0\n");

	return sprintf(buf, "%d\n", 1000 * (data->temp_min[attr->index] - 64));
}
