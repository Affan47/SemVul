show_fan_min(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct lm85_data *data = lm85_update_device(dev);
	return sprintf(buf, "%d\n", FAN_FROM_REG(data->fan_min[nr]));
}
