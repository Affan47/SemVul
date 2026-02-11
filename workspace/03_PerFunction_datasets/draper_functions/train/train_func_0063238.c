isl1208_i2c_read_alarm(struct i2c_client *client, struct rtc_wkalrm *alarm)
{
	struct rtc_time *const tm = &alarm->time;
	u8 regs[ISL1208_ALARM_SECTION_LEN] = { 0, };
	int icr, yr, sr = isl1208_i2c_get_sr(client);

	if (sr < 0) {
		dev_err(&client->dev, "%s: reading SR failed\n", __func__);
		return sr;
	}

	sr = isl1208_i2c_read_regs(client, ISL1208_REG_SCA, regs,
				   ISL1208_ALARM_SECTION_LEN);
	if (sr < 0) {
		dev_err(&client->dev, "%s: reading alarm section failed\n",
			__func__);
		return sr;
	}


	tm->tm_sec = bcd2bin(regs[ISL1208_REG_SCA - ISL1208_REG_SCA] & 0x7f);
	tm->tm_min = bcd2bin(regs[ISL1208_REG_MNA - ISL1208_REG_SCA] & 0x7f);
	tm->tm_hour = bcd2bin(regs[ISL1208_REG_HRA - ISL1208_REG_SCA] & 0x3f);
	tm->tm_mday = bcd2bin(regs[ISL1208_REG_DTA - ISL1208_REG_SCA] & 0x3f);
	tm->tm_mon =
		bcd2bin(regs[ISL1208_REG_MOA - ISL1208_REG_SCA] & 0x1f) - 1;
	tm->tm_wday = bcd2bin(regs[ISL1208_REG_DWA - ISL1208_REG_SCA] & 0x03);


	yr = i2c_smbus_read_byte_data(client, ISL1208_REG_YR);
	if (yr < 0) {
		dev_err(&client->dev, "%s: reading RTC YR failed\n", __func__);
		return yr;
	}
	tm->tm_year = bcd2bin(yr) + 100;

	icr = i2c_smbus_read_byte_data(client, ISL1208_REG_INT);
	if (icr < 0) {
		dev_err(&client->dev, "%s: reading INT failed\n", __func__);
		return icr;
	}
	alarm->enabled = !!(icr & ISL1208_REG_INT_ALME);

	return 0;
}
