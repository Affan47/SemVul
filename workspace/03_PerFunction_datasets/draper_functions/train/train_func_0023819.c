ak8975_who_i_am(struct i2c_client *client,
			   enum asahi_compass_chipset type)
{
	u8 wia_val[2];
	int ret;


	ret = i2c_smbus_read_i2c_block_data(client, AK09912_REG_WIA1,
					    2, wia_val);
	if (ret < 0) {
		dev_err(&client->dev, "Error reading WIA\n");
		return ret;
	}

	if (wia_val[0] != AK8975_DEVICE_ID)
		return -ENODEV;

	switch (type) {
	case AK8975:
	case AK8963:
		return 0;
	case AK09911:
		if (wia_val[1] == AK09911_DEVICE_ID)
			return 0;
		break;
	case AK09912:
		if (wia_val[1] == AK09912_DEVICE_ID)
			return 0;
		break;
	default:
		dev_err(&client->dev, "Type %d unknown\n", type);
	}
	return -ENODEV;
}
