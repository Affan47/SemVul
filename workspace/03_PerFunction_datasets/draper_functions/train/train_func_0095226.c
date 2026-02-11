set_fan(struct device *dev, struct device_attribute *devattr,
		       const char *buf, size_t count)
{
	struct emc6w201_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int sf = to_sensor_dev_attr_2(devattr)->index;
	int nr = to_sensor_dev_attr_2(devattr)->nr;
	int err;
	unsigned long val;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;

	if (val == 0) {
		val = 0xFFFF;
	} else {
		val = DIV_ROUND_CLOSEST(5400000U, val);
		val = clamp_val(val, 0, 0xFFFE);
	}

	mutex_lock(&data->update_lock);
	data->fan[sf][nr] = val;
	err = emc6w201_write16(client, EMC6W201_REG_FAN_MIN(nr),
			       data->fan[sf][nr]);
	mutex_unlock(&data->update_lock);

	return err < 0 ? err : count;
}
