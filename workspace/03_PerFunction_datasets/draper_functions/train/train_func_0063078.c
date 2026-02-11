isl1208_i2c_read_time(struct i2c_client *client, struct rtc_time *tm)
{
	int sr;
	u8 regs[ISL1208_RTC_SECTION_LEN] = { 0, };

	sr = isl1208_i2c_get_sr(client);
	if (sr < 0) {
		dev_err(&client->dev, "%s: reading SR failed\n", __func__);
		return -EIO;
	}

	sr = isl1208_i2c_read_regs(client, 0, regs, ISL1208_RTC_SECTION_LEN);
	if (sr < 0) {
		dev_err(&client->dev, "%s: reading RTC section failed\n",
			__func__);
		return sr;
	}

	tm->tm_sec = bcd2bin(regs[ISL1208_REG_SC]);
	tm->tm_min = bcd2bin(regs[ISL1208_REG_MN]);


	{
		const u8 _hr = regs[ISL1208_REG_HR];
		if (_hr & ISL1208_REG_HR_MIL)
			tm->tm_hour = bcd2bin(_hr & 0x3f);
		else {

			tm->tm_hour = bcd2bin(_hr & 0x1f);
			if (_hr & ISL1208_REG_HR_PM)
				tm->tm_hour += 12;
		}
	}

	tm->tm_mday = bcd2bin(regs[ISL1208_REG_DT]);
	tm->tm_mon = bcd2bin(regs[ISL1208_REG_MO]) - 1;
	tm->tm_year = bcd2bin(regs[ISL1208_REG_YR]) + 100;
	tm->tm_wday = bcd2bin(regs[ISL1208_REG_DW]);

	return 0;
}
