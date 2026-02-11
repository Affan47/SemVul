pcf85063_get_datetime(struct i2c_client *client, struct rtc_time *tm)
{
	struct pcf85063 *pcf85063 = i2c_get_clientdata(client);
	unsigned char buf[13] = { PCF85063_REG_CTRL1 };
	struct i2c_msg msgs[] = {
		{
			.addr = client->addr,
			.len = 1,
			.buf = buf
		},
		{
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 13,
			.buf = buf
		},
	};


	if ((i2c_transfer(client->adapter, msgs, 2)) != 2) {
		dev_err(&client->dev, "%s: read error\n", __func__);
		return -EIO;
	}

	tm->tm_sec = bcd2bin(buf[PCF85063_REG_SC] & 0x7F);
	tm->tm_min = bcd2bin(buf[PCF85063_REG_MN] & 0x7F);
	tm->tm_hour = bcd2bin(buf[PCF85063_REG_HR] & 0x3F);
	tm->tm_mday = bcd2bin(buf[PCF85063_REG_DM] & 0x3F);
	tm->tm_wday = buf[PCF85063_REG_DW] & 0x07;
	tm->tm_mon = bcd2bin(buf[PCF85063_REG_MO] & 0x1F) - 1;
	tm->tm_year = bcd2bin(buf[PCF85063_REG_YR]);
	if (tm->tm_year < 70)
		tm->tm_year += 100;

	pcf85063->c_polarity = (buf[PCF85063_REG_MO] & PCF85063_MO_C) ?
		(tm->tm_year >= 100) : (tm->tm_year < 100);

	return rtc_valid_tm(tm);
}
