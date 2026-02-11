pcf2127_get_datetime(struct i2c_client *client, struct rtc_time *tm)
{
	unsigned char buf[10] = { PCF2127_REG_CTRL1 };


	if (i2c_master_send(client, buf, 1) != 1 ||
		i2c_master_recv(client, buf, sizeof(buf)) != sizeof(buf)) {
		dev_err(&client->dev, "%s: read error\n", __func__);
		return -EIO;
	}

	if (buf[PCF2127_REG_CTRL3] & PCF2127_REG_CTRL3_BLF)
		dev_info(&client->dev,
			"low voltage detected, check/replace RTC battery.\n");

	if (buf[PCF2127_REG_SC] & PCF2127_OSF) {


		dev_warn(&client->dev,
			 "oscillator stop detected, date/time is not reliable\n");
		return -EINVAL;
	}

	dev_dbg(&client->dev,
		"%s: raw data is cr1=%02x, cr2=%02x, cr3=%02x, "
		"sec=%02x, min=%02x, hr=%02x, "
		"mday=%02x, wday=%02x, mon=%02x, year=%02x\n",
		__func__,
		buf[0], buf[1], buf[2],
		buf[3], buf[4], buf[5],
		buf[6], buf[7], buf[8], buf[9]);


	tm->tm_sec = bcd2bin(buf[PCF2127_REG_SC] & 0x7F);
	tm->tm_min = bcd2bin(buf[PCF2127_REG_MN] & 0x7F);
	tm->tm_hour = bcd2bin(buf[PCF2127_REG_HR] & 0x3F);
	tm->tm_mday = bcd2bin(buf[PCF2127_REG_DM] & 0x3F);
	tm->tm_wday = buf[PCF2127_REG_DW] & 0x07;
	tm->tm_mon = bcd2bin(buf[PCF2127_REG_MO] & 0x1F) - 1;
	tm->tm_year = bcd2bin(buf[PCF2127_REG_YR]);
	if (tm->tm_year < 70)
		tm->tm_year += 100;

	dev_dbg(&client->dev, "%s: tm is secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_hour,
		tm->tm_mday, tm->tm_mon, tm->tm_year, tm->tm_wday);

	return rtc_valid_tm(tm);
}
