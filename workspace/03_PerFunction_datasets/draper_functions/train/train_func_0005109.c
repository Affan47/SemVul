smsc47m192_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct smsc47m192_data *data;
	int config;

	data = devm_kzalloc(dev, sizeof(struct smsc47m192_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	data->vrm = vid_which_vrm();
	mutex_init(&data->update_lock);


	smsc47m192_init_client(client);


	data->groups[0] = &smsc47m192_group;

	config = i2c_smbus_read_byte_data(client, SMSC47M192_REG_CONFIG);
	if (!(config & 0x20))
		data->groups[1] = &smsc47m192_group_in4;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data, data->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}
