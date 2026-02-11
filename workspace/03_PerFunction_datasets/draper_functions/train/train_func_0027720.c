atxp1_storegpio1(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t count)
{
	struct atxp1_data *data = atxp1_update_device(dev);
	struct i2c_client *client = data->client;
	unsigned long value;
	int err;

	err = kstrtoul(buf, 16, &value);
	if (err)
		return err;

	value &= ATXP1_GPIO1MASK;

	if (value != (data->reg.gpio1 & ATXP1_GPIO1MASK)) {
		dev_info(dev, "Writing 0x%x to GPIO1.\n", (unsigned int)value);

		i2c_smbus_write_byte_data(client, ATXP1_GPIO1, value);

		data->valid = 0;
	}

	return count;
}
