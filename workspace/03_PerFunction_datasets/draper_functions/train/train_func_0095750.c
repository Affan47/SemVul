set_type(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct lm95234_data *data = dev_get_drvdata(dev);
	unsigned long val;
	u8 mask = to_sensor_dev_attr(attr)->index;
	int ret = lm95234_update_device(data);

	if (ret)
		return ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret < 0)
		return ret;

	if (val != 1 && val != 2)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	if (val == 1)
		data->sensor_type |= mask;
	else
		data->sensor_type &= ~mask;
	data->valid = false;
	i2c_smbus_write_byte_data(data->client, LM95234_REG_REM_MODEL,
				  data->sensor_type);
	mutex_unlock(&data->update_lock);

	return count;
}
