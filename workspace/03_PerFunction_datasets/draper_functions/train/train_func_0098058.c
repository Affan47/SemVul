lm95245_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct lm95245_data *data;
	struct device *hwmon_dev;

	data = devm_kzalloc(dev, sizeof(struct lm95245_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);


	lm95245_init_client(client, data);

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data,
							   lm95245_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}
