lm93_detect(struct i2c_client *client, struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int mfr, ver;
	const char *name;

	if (!i2c_check_functionality(adapter, LM93_SMBUS_FUNC_MIN))
		return -ENODEV;


	mfr = lm93_read_byte(client, LM93_REG_MFR_ID);
	if (mfr != 0x01) {
		dev_dbg(&adapter->dev,
			"detect failed, bad manufacturer id 0x%02x!\n", mfr);
		return -ENODEV;
	}

	ver = lm93_read_byte(client, LM93_REG_VER);
	switch (ver) {
	case LM93_MFR_ID:
	case LM93_MFR_ID_PROTOTYPE:
		name = "lm93";
		break;
	case LM94_MFR_ID_2:
	case LM94_MFR_ID:
	case LM94_MFR_ID_PROTOTYPE:
		name = "lm94";
		break;
	default:
		dev_dbg(&adapter->dev,
			"detect failed, bad version id 0x%02x!\n", ver);
		return -ENODEV;
	}

	strlcpy(info->type, name, I2C_NAME_SIZE);
	dev_dbg(&adapter->dev, "loading %s at %d, 0x%02x\n",
		client->name, i2c_adapter_id(client->adapter),
		client->addr);

	return 0;
}
