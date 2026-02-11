elan_smbus_initialize(struct i2c_client *client)
{
	u8 check[ETP_SMBUS_HELLOPACKET_LEN] = { 0x55, 0x55, 0x55, 0x55, 0x55 };
	u8 values[ETP_SMBUS_HELLOPACKET_LEN] = { 0, 0, 0, 0, 0 };
	int len, error;


	len = i2c_smbus_read_block_data(client,
					ETP_SMBUS_HELLOPACKET_CMD, values);
	if (len != ETP_SMBUS_HELLOPACKET_LEN) {
		dev_err(&client->dev, "hello packet length fail: %d\n", len);
		error = len < 0 ? len : -EIO;
		return error;
	}


	if (memcmp(values, check, ETP_SMBUS_HELLOPACKET_LEN)) {
		dev_err(&client->dev, "hello packet fail [%*ph]\n",
			ETP_SMBUS_HELLOPACKET_LEN, values);
		return -ENXIO;
	}


	error = i2c_smbus_write_byte(client, ETP_SMBUS_ENABLE_TP);
	if (error) {
		dev_err(&client->dev, "failed to enable touchpad: %d\n", error);
		return error;
	}

	return 0;
}
