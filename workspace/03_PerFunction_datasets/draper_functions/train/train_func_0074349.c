set_beep_enable(struct device *dev, struct device_attribute
			       *attr, const char *buf, size_t count)
{
	struct gl520_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	u8 r;
	unsigned long v;
	int err;

	err = kstrtoul(buf, 10, &v);
	if (err)
		return err;

	r = (v ? 0 : 1);

	mutex_lock(&data->update_lock);
	data->beep_enable = !r;
	gl520_write_value(client, GL520_REG_BEEP_ENABLE,
			  (gl520_read_value(client, GL520_REG_BEEP_ENABLE)
			   & ~0x04) | (r << 2));
	mutex_unlock(&data->update_lock);
	return count;
}
