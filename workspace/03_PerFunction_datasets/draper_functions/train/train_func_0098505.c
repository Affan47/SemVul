isl1208_rtc_toggle_alarm(struct i2c_client *client, int enable)
{
	int icr = i2c_smbus_read_byte_data(client, ISL1208_REG_INT);

	if (icr < 0) {
		dev_err(&client->dev, "%s: reading INT failed\n", __func__);
		return icr;
	}

	if (enable)
		icr |= ISL1208_REG_INT_ALME | ISL1208_REG_INT_IM;
	else
		icr &= ~(ISL1208_REG_INT_ALME | ISL1208_REG_INT_IM);

	icr = i2c_smbus_write_byte_data(client, ISL1208_REG_INT, icr);
	if (icr < 0) {
		dev_err(&client->dev, "%s: writing INT failed\n", __func__);
		return icr;
	}

	return 0;
}
