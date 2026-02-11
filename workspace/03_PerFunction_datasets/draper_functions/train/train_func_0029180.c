emc6w201_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct emc6w201_data *data;
	struct device *hwmon_dev;

	data = devm_kzalloc(dev, sizeof(struct emc6w201_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data,
							   emc6w201_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}
