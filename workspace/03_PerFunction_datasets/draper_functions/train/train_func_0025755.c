isl1208_i2c_set_time(struct i2c_client *client, struct rtc_time const *tm)
{
	int sr;
	u8 regs[ISL1208_RTC_SECTION_LEN] = { 0, };


	if (tm->tm_year < 100)
		return -EINVAL;

	regs[ISL1208_REG_SC] = bin2bcd(tm->tm_sec);
	regs[ISL1208_REG_MN] = bin2bcd(tm->tm_min);
	regs[ISL1208_REG_HR] = bin2bcd(tm->tm_hour) | ISL1208_REG_HR_MIL;

	regs[ISL1208_REG_DT] = bin2bcd(tm->tm_mday);
	regs[ISL1208_REG_MO] = bin2bcd(tm->tm_mon + 1);
	regs[ISL1208_REG_YR] = bin2bcd(tm->tm_year - 100);

	regs[ISL1208_REG_DW] = bin2bcd(tm->tm_wday & 7);

	sr = isl1208_i2c_get_sr(client);
	if (sr < 0) {
		dev_err(&client->dev, "%s: reading SR failed\n", __func__);
		return sr;
	}


	sr = i2c_smbus_write_byte_data(client, ISL1208_REG_SR,
				       sr | ISL1208_REG_SR_WRTC);
	if (sr < 0) {
		dev_err(&client->dev, "%s: writing SR failed\n", __func__);
		return sr;
	}


	sr = isl1208_i2c_set_regs(client, 0, regs, ISL1208_RTC_SECTION_LEN);
	if (sr < 0) {
		dev_err(&client->dev, "%s: writing RTC section failed\n",
			__func__);
		return sr;
	}


	sr = i2c_smbus_write_byte_data(client, ISL1208_REG_SR,
				       sr & ~ISL1208_REG_SR_WRTC);
	if (sr < 0) {
		dev_err(&client->dev, "%s: writing SR failed\n", __func__);
		return sr;
	}

	return 0;
}
