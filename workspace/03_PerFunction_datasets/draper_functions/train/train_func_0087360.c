set_fan_min(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct gl520_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int n = to_sensor_dev_attr(attr)->index;
	u8 r;
	unsigned long v;
	int err;

	err = kstrtoul(buf, 10, &v);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	r = FAN_TO_REG(v, data->fan_div[n]);
	data->fan_min[n] = r;

	if (n == 0)
		gl520_write_value(client, GL520_REG_FAN_MIN,
				  (gl520_read_value(client, GL520_REG_FAN_MIN)
				   & ~0xff00) | (r << 8));
	else
		gl520_write_value(client, GL520_REG_FAN_MIN,
				  (gl520_read_value(client, GL520_REG_FAN_MIN)
				   & ~0xff) | r);

	data->beep_mask = gl520_read_value(client, GL520_REG_BEEP_MASK);
	if (data->fan_min[n] == 0)
		data->alarm_mask &= (n == 0) ? ~0x20 : ~0x40;
	else
		data->alarm_mask |= (n == 0) ? 0x20 : 0x40;
	data->beep_mask &= data->alarm_mask;
	gl520_write_value(client, GL520_REG_BEEP_MASK, data->beep_mask);

	mutex_unlock(&data->update_lock);
	return count;
}
