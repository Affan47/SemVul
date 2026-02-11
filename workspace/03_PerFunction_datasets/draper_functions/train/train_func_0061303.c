show_in(struct device *dev, struct device_attribute *da,
	char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct i2c_client *client = to_i2c_client(dev);
	int res;
	int index = attr->index;

	res = ads1015_read_adc(client, index);
	if (res < 0)
		return res;

	return sprintf(buf, "%d\n", ads1015_reg_to_mv(client, index, res));
}
