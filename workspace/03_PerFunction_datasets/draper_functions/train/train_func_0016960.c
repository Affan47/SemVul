regs_to_tm(u8 *regs, struct rtc_time *tm)
{
	tm->tm_year = bcd2bin(regs[RTC_YEAR2]) * 100 +
		bcd2bin(regs[RTC_YEAR1]) - 1900;
	tm->tm_mon = bcd2bin(regs[RTC_MONTH] & 0x1f) - 1;
	tm->tm_mday = bcd2bin(regs[RTC_DATE] & 0x3f);
	tm->tm_wday = (regs[RTC_WEEKDAY] & 0x07);
	if (regs[RTC_HOUR] & HOUR_12) {
		tm->tm_hour = bcd2bin(regs[RTC_HOUR] & 0x01f);
		if (tm->tm_hour == 12)
			tm->tm_hour = 0;
		if (regs[RTC_HOUR] & HOUR_AM_PM)
			tm->tm_hour += 12;
	} else {
		tm->tm_hour = bcd2bin(regs[RTC_HOUR] & 0x03f);
	}
	tm->tm_min = bcd2bin(regs[RTC_MIN] & 0x7f);
	tm->tm_sec = bcd2bin(regs[RTC_SEC] & 0x7f);
}
