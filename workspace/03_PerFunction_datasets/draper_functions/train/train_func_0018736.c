set_in_min(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;
	struct adm1026_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	data->in_min[nr] = INS_TO_REG(nr, val);
	adm1026_write_value(client, ADM1026_REG_IN_MIN[nr], data->in_min[nr]);
	mutex_unlock(&data->update_lock);
	return count;
}
