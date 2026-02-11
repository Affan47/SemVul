ds1511_rtc_set_time(struct device *dev, struct rtc_time *rtc_tm)
{
	u8 mon, day, dow, hrs, min, sec, yrs, cen;
	unsigned long flags;


	if (rtc_tm->tm_year < 1900)
		rtc_tm->tm_year += 1900;

	if (rtc_tm->tm_year < 1970)
		return -EINVAL;

	yrs = rtc_tm->tm_year % 100;
	cen = rtc_tm->tm_year / 100;
	mon = rtc_tm->tm_mon + 1;
	day = rtc_tm->tm_mday;
	dow = rtc_tm->tm_wday & 0x7;
	hrs = rtc_tm->tm_hour;
	min = rtc_tm->tm_min;
	sec = rtc_tm->tm_sec;

	if ((mon > 12) || (day == 0))
		return -EINVAL;

	if (day > rtc_month_days(rtc_tm->tm_mon, rtc_tm->tm_year))
		return -EINVAL;

	if ((hrs >= 24) || (min >= 60) || (sec >= 60))
		return -EINVAL;


	sec = bin2bcd(sec) & 0x7f;
	min = bin2bcd(min) & 0x7f;
	hrs = bin2bcd(hrs) & 0x3f;
	day = bin2bcd(day) & 0x3f;
	mon = bin2bcd(mon) & 0x1f;
	yrs = bin2bcd(yrs) & 0xff;
	cen = bin2bcd(cen) & 0xff;

	spin_lock_irqsave(&ds1511_lock, flags);
	rtc_disable_update();
	rtc_write(cen, RTC_CENTURY);
	rtc_write(yrs, RTC_YEAR);
	rtc_write((rtc_read(RTC_MON) & 0xe0) | mon, RTC_MON);
	rtc_write(day, RTC_DOM);
	rtc_write(hrs, RTC_HOUR);
	rtc_write(min, RTC_MIN);
	rtc_write(sec, RTC_SEC);
	rtc_write(dow, RTC_DOW);
	rtc_enable_update();
	spin_unlock_irqrestore(&ds1511_lock, flags);

	return 0;
}
