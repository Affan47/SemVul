moxart_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct moxart_rtc *moxart_rtc = dev_get_drvdata(dev);
	unsigned char v;

	spin_lock_irq(&moxart_rtc->rtc_lock);

	v = moxart_rtc_read_register(dev, GPIO_RTC_SECONDS_R);
	tm->tm_sec = (((v & 0x70) >> 4) * 10) + (v & 0x0F);

	v = moxart_rtc_read_register(dev, GPIO_RTC_MINUTES_R);
	tm->tm_min = (((v & 0x70) >> 4) * 10) + (v & 0x0F);

	v = moxart_rtc_read_register(dev, GPIO_RTC_HOURS_R);
	if (v & 0x80) {
		tm->tm_hour = (((v & 0x10) >> 4) * 10) + (v & 0x0F);
		if (v & 0x20) {
			tm->tm_hour += 12;
			if (tm->tm_hour >= 24)
				tm->tm_hour = 0;
		}
	} else {
		tm->tm_hour = (((v & 0x30) >> 4) * 10) + (v & 0x0F);
	}

	v = moxart_rtc_read_register(dev, GPIO_RTC_DATE_R);
	tm->tm_mday = (((v & 0x30) >> 4) * 10) + (v & 0x0F);

	v = moxart_rtc_read_register(dev, GPIO_RTC_MONTH_R);
	tm->tm_mon = (((v & 0x10) >> 4) * 10) + (v & 0x0F);
	tm->tm_mon--;

	v = moxart_rtc_read_register(dev, GPIO_RTC_YEAR_R);
	tm->tm_year = (((v & 0xF0) >> 4) * 10) + (v & 0x0F);
	tm->tm_year += 100;
	if (tm->tm_year <= 69)
		tm->tm_year += 100;

	v = moxart_rtc_read_register(dev, GPIO_RTC_DAY_R);
	tm->tm_wday = (v & 0x0f) - 1;
	tm->tm_yday = day_of_year[tm->tm_mon];
	tm->tm_yday += (tm->tm_mday - 1);
	if (tm->tm_mon >= 2) {
		if (!(tm->tm_year % 4) && (tm->tm_year % 100))
			tm->tm_yday++;
	}

	tm->tm_isdst = 0;

	spin_unlock_irq(&moxart_rtc->rtc_lock);

	return 0;
}
