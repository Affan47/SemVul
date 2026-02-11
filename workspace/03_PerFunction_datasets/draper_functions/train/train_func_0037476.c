store_beep(struct device *dev, struct device_attribute *attr,
	   const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct w83795_data *data = i2c_get_clientdata(client);
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int index = sensor_attr->index >> 3;
	int shift = sensor_attr->index & 0x07;
	u8 beep_bit = 1 << shift;
	unsigned long val;

	if (kstrtoul(buf, 10, &val) < 0)
		return -EINVAL;
	if (val != 0 && val != 1)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	data->beeps[index] = w83795_read(client, W83795_REG_BEEP(index));
	data->beeps[index] &= ~beep_bit;
	data->beeps[index] |= val << shift;
	w83795_write(client, W83795_REG_BEEP(index), data->beeps[index]);
	mutex_unlock(&data->update_lock);

	return count;
}
