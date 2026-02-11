fm3130_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct fm3130 *fm3130 = dev_get_drvdata(dev);
	struct rtc_time *tm = &alrm->time;
	int i;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"write alarm", tm->tm_sec, tm->tm_min,
		tm->tm_hour, tm->tm_mday,
		tm->tm_mon, tm->tm_year, tm->tm_wday);

	fm3130->regs[FM3130_ALARM_SECONDS] =
		(tm->tm_sec != -1) ? bin2bcd(tm->tm_sec) : 0x80;

	fm3130->regs[FM3130_ALARM_MINUTES] =
		(tm->tm_min != -1) ? bin2bcd(tm->tm_min) : 0x80;

	fm3130->regs[FM3130_ALARM_HOURS] =
		(tm->tm_hour != -1) ? bin2bcd(tm->tm_hour) : 0x80;

	fm3130->regs[FM3130_ALARM_DATE] =
		(tm->tm_mday != -1) ? bin2bcd(tm->tm_mday) : 0x80;

	fm3130->regs[FM3130_ALARM_MONTHS] =
		(tm->tm_mon != -1) ? bin2bcd(tm->tm_mon + 1) : 0x80;

	dev_dbg(dev, "alarm write %02x %02x %02x %02x %02x\n",
			fm3130->regs[FM3130_ALARM_SECONDS],
			fm3130->regs[FM3130_ALARM_MINUTES],
			fm3130->regs[FM3130_ALARM_HOURS],
			fm3130->regs[FM3130_ALARM_DATE],
			fm3130->regs[FM3130_ALARM_MONTHS]);

	for (i = 0; i < FM3130_ALARM_REGS; i++) {
		i2c_smbus_write_byte_data(fm3130->client,
					FM3130_ALARM_SECONDS + i,
					fm3130->regs[FM3130_ALARM_SECONDS + i]);
	}
	fm3130->regs[FM3130_RTC_CONTROL] =
		i2c_smbus_read_byte_data(fm3130->client, FM3130_RTC_CONTROL);


	if (alrm->enabled) {
		i2c_smbus_write_byte_data(fm3130->client, FM3130_RTC_CONTROL,
			(fm3130->regs[FM3130_RTC_CONTROL] &
				~(FM3130_RTC_CONTROL_BIT_CAL)) |
					FM3130_RTC_CONTROL_BIT_AEN);
	} else {
		i2c_smbus_write_byte_data(fm3130->client, FM3130_RTC_CONTROL,
			fm3130->regs[FM3130_RTC_CONTROL] &
				~(FM3130_RTC_CONTROL_BIT_CAL) &
					~(FM3130_RTC_CONTROL_BIT_AEN));
	}


	if (!fm3130->alarm_valid)
		fm3130->alarm_valid = 1;

	return 0;
}
