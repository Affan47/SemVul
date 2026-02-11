set_pwm_auto_pwm_minctl(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct lm85_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	u8 tmp;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	data->autofan[nr].min_off = val;
	tmp = lm85_read_value(client, LM85_REG_AFAN_SPIKE1);
	tmp &= ~(0x20 << nr);
	if (data->autofan[nr].min_off)
		tmp |= 0x20 << nr;
	lm85_write_value(client, LM85_REG_AFAN_SPIKE1, tmp);
	mutex_unlock(&data->update_lock);
	return count;
}
