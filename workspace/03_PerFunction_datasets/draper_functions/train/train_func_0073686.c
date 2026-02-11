max6875_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct max6875_data *data;
	int err;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WRITE_BYTE_DATA
				     | I2C_FUNC_SMBUS_READ_BYTE))
		return -ENODEV;


	if (client->addr & 1)
		return -ENODEV;

	if (!(data = kzalloc(sizeof(struct max6875_data), GFP_KERNEL)))
		return -ENOMEM;


	data->fake_client = i2c_new_dummy(client->adapter, client->addr + 1);
	if (!data->fake_client) {
		err = -ENOMEM;
		goto exit_kfree;
	}


	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	err = sysfs_create_bin_file(&client->dev.kobj, &user_eeprom_attr);
	if (err)
		goto exit_remove_fake;

	return 0;

exit_remove_fake:
	i2c_unregister_device(data->fake_client);
exit_kfree:
	kfree(data);
	return err;
}
