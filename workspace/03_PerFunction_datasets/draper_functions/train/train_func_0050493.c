w83792d_remove(struct i2c_client *client)
{
	struct w83792d_data *data = i2c_get_clientdata(client);
	int i;

	hwmon_device_unregister(data->hwmon_dev);
	sysfs_remove_group(&client->dev.kobj, &w83792d_group);
	for (i = 0; i < ARRAY_SIZE(w83792d_group_fan); i++)
		sysfs_remove_group(&client->dev.kobj,
				   &w83792d_group_fan[i]);

	if (data->lm75[0] != NULL)
		i2c_unregister_device(data->lm75[0]);
	if (data->lm75[1] != NULL)
		i2c_unregister_device(data->lm75[1]);

	return 0;
}
