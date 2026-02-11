adm1029_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct adm1029_data *data;
	struct device *hwmon_dev;

	data = devm_kzalloc(dev, sizeof(struct adm1029_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);


	if (adm1029_init_client(client) == 0)
		return -ENODEV;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data,
							   adm1029_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}
