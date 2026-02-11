_abb5zes3_rtc_read_alarm(struct device *dev,
				    struct rtc_wkalrm *alarm)
{
	struct abb5zes3_rtc_data *data = dev_get_drvdata(dev);
	struct rtc_time rtc_tm, *alarm_tm = &alarm->time;
	unsigned long rtc_secs, alarm_secs;
	u8 regs[ABB5ZES3_ALRM_SEC_LEN];
	unsigned int reg;
	int ret;

	ret = regmap_bulk_read(data->regmap, ABB5ZES3_REG_ALRM_MN, regs,
			       ABB5ZES3_ALRM_SEC_LEN);
	if (ret) {
		dev_err(dev, "%s: reading alarm section failed (%d)\n",
			__func__, ret);
		goto err;
	}

	alarm_tm->tm_sec  = 0;
	alarm_tm->tm_min  = bcd2bin(regs[0] & 0x7f);
	alarm_tm->tm_hour = bcd2bin(regs[1] & 0x3f);
	alarm_tm->tm_mday = bcd2bin(regs[2] & 0x3f);
	alarm_tm->tm_wday = -1;


	ret = _abb5zes3_rtc_read_time(dev, &rtc_tm);
	if (ret)
		goto err;

	alarm_tm->tm_year = rtc_tm.tm_year;
	alarm_tm->tm_mon = rtc_tm.tm_mon;

	ret = rtc_tm_to_time(&rtc_tm, &rtc_secs);
	if (ret)
		goto err;

	ret = rtc_tm_to_time(alarm_tm, &alarm_secs);
	if (ret)
		goto err;

	if (alarm_secs < rtc_secs) {
		if (alarm_tm->tm_mon == 11) {
			alarm_tm->tm_mon = 0;
			alarm_tm->tm_year += 1;
		} else {
			alarm_tm->tm_mon += 1;
		}
	}

	ret = regmap_read(data->regmap, ABB5ZES3_REG_CTRL1, &reg);
	if (ret) {
		dev_err(dev, "%s: reading ctrl reg failed (%d)\n",
			__func__, ret);
		goto err;
	}

	alarm->enabled = !!(reg & ABB5ZES3_REG_CTRL1_AIE);

err:
	return ret;
}
