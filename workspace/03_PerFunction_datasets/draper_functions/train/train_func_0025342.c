show_temp_value(struct device *dev, struct device_attribute
	*devattr, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct sch5636_data *data = sch5636_update_device(dev);
	int val;

	if (IS_ERR(data))
		return PTR_ERR(data);

	val = (data->temp_val[attr->index] - 64) * 1000;
	return snprintf(buf, PAGE_SIZE, "%d\n", val);
}
