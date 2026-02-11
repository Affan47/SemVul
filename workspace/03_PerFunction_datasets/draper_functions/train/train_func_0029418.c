show_fan_input(struct device *dev,
			      struct device_attribute *dev_attr, char *buf)
{
	struct max6639_data *data = max6639_update_device(dev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);

	if (IS_ERR(data))
		return PTR_ERR(data);

	return sprintf(buf, "%d\n", FAN_FROM_REG(data->fan[attr->index],
		       data->rpm_range));
}
