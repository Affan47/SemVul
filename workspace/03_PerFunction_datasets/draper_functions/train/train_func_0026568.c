adt7462_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct adt7462_data *data;
	struct device *hwmon_dev;

	data = devm_kzalloc(dev, sizeof(struct adt7462_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->lock);

	dev_info(&client->dev, "%s chip found\n", client->name);

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data,
							   adt7462_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}
