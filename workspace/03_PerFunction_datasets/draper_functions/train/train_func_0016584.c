set_in_max(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;
	struct smsc47m192_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	data->in_max[nr] = IN_TO_REG(val, nr);
	i2c_smbus_write_byte_data(client, SMSC47M192_REG_IN_MAX(nr),
							data->in_max[nr]);
	mutex_unlock(&data->update_lock);
	return count;
}
