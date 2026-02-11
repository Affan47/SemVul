lm92_update_device(struct device *dev)
{
	struct lm92_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ)
	 || !data->valid) {
		dev_dbg(&client->dev, "Updating lm92 data\n");
		for (i = 0; i < t_num_regs; i++) {
			data->temp[i] =
				i2c_smbus_read_word_swapped(client, regs[i]);
		}
		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}
