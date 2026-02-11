isl12022_set_datetime(struct i2c_client *client, struct rtc_time *tm)
{
	struct isl12022 *isl12022 = i2c_get_clientdata(client);
	size_t i;
	int ret;
	uint8_t buf[ISL12022_REG_DW + 1];

	dev_dbg(&client->dev, "%s: secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_hour,
		tm->tm_mday, tm->tm_mon, tm->tm_year, tm->tm_wday);

	if (!isl12022->write_enabled) {

		ret = isl12022_read_regs(client, ISL12022_REG_INT, buf, 1);
		if (ret)
			return ret;


		if (!(buf[0] & ISL12022_INT_WRTC)) {
			dev_info(&client->dev,
				 "init write enable and 24 hour format\n");


			ret = isl12022_write_reg(client,
						 ISL12022_REG_INT,
						 buf[0] | ISL12022_INT_WRTC);
			if (ret)
				return ret;


			ret = isl12022_read_regs(client, ISL12022_REG_HR,
						 buf, 1);
			if (ret)
				return ret;

			ret = isl12022_write_reg(client,
						 ISL12022_REG_HR,
						 buf[0] | ISL12022_HR_MIL);
			if (ret)
				return ret;
		}

		isl12022->write_enabled = 1;
	}


	buf[ISL12022_REG_SC] = bin2bcd(tm->tm_sec);
	buf[ISL12022_REG_MN] = bin2bcd(tm->tm_min);
	buf[ISL12022_REG_HR] = bin2bcd(tm->tm_hour) | ISL12022_HR_MIL;

	buf[ISL12022_REG_DT] = bin2bcd(tm->tm_mday);


	buf[ISL12022_REG_MO] = bin2bcd(tm->tm_mon + 1);


	buf[ISL12022_REG_YR] = bin2bcd(tm->tm_year % 100);

	buf[ISL12022_REG_DW] = tm->tm_wday & 0x07;


	for (i = 0; i < ARRAY_SIZE(buf); i++) {
		ret = isl12022_write_reg(client, ISL12022_REG_SC + i,
					 buf[ISL12022_REG_SC + i]);
		if (ret)
			return -EIO;
	}

	return 0;
}
