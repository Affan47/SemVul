vz89x_get_measurement(struct vz89x_data *data)
{
	int ret;
	int i;


	if (!time_after(jiffies, data->last_update + HZ))
		return 0;

	ret = i2c_smbus_write_word_data(data->client,
					VZ89X_REG_MEASUREMENT, 0);
	if (ret < 0)
		return ret;

	for (i = 0; i < VZ89X_REG_MEASUREMENT_SIZE; i++) {
		ret = i2c_smbus_read_byte(data->client);
		if (ret < 0)
			return ret;
		data->buffer[i] = ret;
	}

	ret = vz89x_measurement_is_valid(data);
	if (ret)
		return -EAGAIN;

	data->last_update = jiffies;

	return 0;
}
