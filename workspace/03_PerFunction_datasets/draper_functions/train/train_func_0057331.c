ltc2945_show_value(struct device *dev,
				  struct device_attribute *da, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	long long value;

	value = ltc2945_reg_to_val(dev, attr->index);
	if (value < 0)
		return value;
	return snprintf(buf, PAGE_SIZE, "%lld\n", value);
}
