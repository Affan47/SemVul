emc2103_detect(struct i2c_client *new_client, struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = new_client->adapter;
	int manufacturer, product;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	manufacturer = i2c_smbus_read_byte_data(new_client, REG_MFG_ID);
	if (manufacturer != 0x5D)
		return -ENODEV;

	product = i2c_smbus_read_byte_data(new_client, REG_PRODUCT_ID);
	if ((product != 0x24) && (product != 0x26))
		return -ENODEV;

	strlcpy(info->type, "emc2103", I2C_NAME_SIZE);

	return 0;
}
