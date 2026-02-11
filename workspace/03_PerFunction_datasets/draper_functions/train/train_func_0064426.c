tmp102_update_device(struct device *dev)
{
	struct tmp102 *tmp102 = dev_get_drvdata(dev);
	struct i2c_client *client = tmp102->client;

	mutex_lock(&tmp102->lock);
	if (time_after(jiffies, tmp102->last_update + HZ / 3)) {
		int i;
		for (i = 0; i < ARRAY_SIZE(tmp102->temp); ++i) {
			int status = i2c_smbus_read_word_swapped(client,
								 tmp102_reg[i]);
			if (status > -1)
				tmp102->temp[i] = tmp102_reg_to_mC(status);
		}
		tmp102->last_update = jiffies;
		tmp102->first_time = false;
	}
	mutex_unlock(&tmp102->lock);
	return tmp102;
}
