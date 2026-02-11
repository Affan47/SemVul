da9052_set_alarm(struct da9052_rtc *rtc, struct rtc_time *rtc_tm)
{
	struct da9052 *da9052 = rtc->da9052;
	unsigned long alm_time;
	int ret;
	uint8_t v[3];

	ret = rtc_tm_to_time(rtc_tm, &alm_time);
	if (ret != 0)
		return ret;

	if (rtc_tm->tm_sec > 0) {
		alm_time += 60 - rtc_tm->tm_sec;
		rtc_time_to_tm(alm_time, rtc_tm);
	}
	BUG_ON(rtc_tm->tm_sec);

	rtc_tm->tm_year -= 100;
	rtc_tm->tm_mon += 1;

	ret = da9052_reg_update(da9052, DA9052_ALARM_MI_REG,
				DA9052_RTC_MIN, rtc_tm->tm_min);
	if (ret != 0) {
		rtc_err(rtc, "Failed to write ALRM MIN: %d\n", ret);
		return ret;
	}

	v[0] = rtc_tm->tm_hour;
	v[1] = rtc_tm->tm_mday;
	v[2] = rtc_tm->tm_mon;

	ret = da9052_group_write(da9052, DA9052_ALARM_H_REG, 3, v);
	if (ret < 0)
		return ret;

	ret = da9052_reg_update(da9052, DA9052_ALARM_Y_REG,
				DA9052_RTC_YEAR, rtc_tm->tm_year);
	if (ret != 0)
		rtc_err(rtc, "Failed to write ALRM YEAR: %d\n", ret);

	return ret;
}
