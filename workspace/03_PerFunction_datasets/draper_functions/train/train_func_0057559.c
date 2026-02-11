show_temp(struct device *dev, struct device_attribute *da,
			 char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct lm73_data *data = dev_get_drvdata(dev);
	int temp;

	s32 err = i2c_smbus_read_word_swapped(data->client, attr->index);
	if (err < 0)
		return err;


	temp = (((s16) err) * 250) / 32;
	return scnprintf(buf, PAGE_SIZE, "%d\n", temp);
}
