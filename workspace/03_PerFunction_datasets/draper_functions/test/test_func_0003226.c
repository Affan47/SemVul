adm1025_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct adm1025_data *data;
	u8 config;

	data = devm_kzalloc(dev, sizeof(struct adm1025_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->update_lock);


	adm1025_init_client(client);


	data->groups[0] = &adm1025_group;

	config = i2c_smbus_read_byte_data(client, ADM1025_REG_CONFIG);
	if (!(config & 0x20))
		data->groups[1] = &adm1025_group_in4;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data, data->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}
