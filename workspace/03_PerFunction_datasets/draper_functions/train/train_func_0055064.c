adt7462_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int vendor, device, revision;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	vendor = i2c_smbus_read_byte_data(client, ADT7462_REG_VENDOR);
	if (vendor != ADT7462_VENDOR)
		return -ENODEV;

	device = i2c_smbus_read_byte_data(client, ADT7462_REG_DEVICE);
	if (device != ADT7462_DEVICE)
		return -ENODEV;

	revision = i2c_smbus_read_byte_data(client, ADT7462_REG_REVISION);
	if (revision != ADT7462_REVISION)
		return -ENODEV;

	strlcpy(info->type, "adt7462", I2C_NAME_SIZE);

	return 0;
}
