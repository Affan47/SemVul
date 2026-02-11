adm1031_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	const char *name;
	int id, co;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	id = i2c_smbus_read_byte_data(client, 0x3d);
	co = i2c_smbus_read_byte_data(client, 0x3e);

	if (!((id == 0x31 || id == 0x30) && co == 0x41))
		return -ENODEV;
	name = (id == 0x30) ? "adm1030" : "adm1031";

	strlcpy(info->type, name, I2C_NAME_SIZE);

	return 0;
}
