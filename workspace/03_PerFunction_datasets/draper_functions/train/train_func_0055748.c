lp8788_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct lp8788_rtc *rtc = dev_get_drvdata(dev);
	struct lp8788 *lp = rtc->lp;
	struct rtc_time *tm = &alarm->time;
	u8 addr, data[LPTIME_MAX];
	int ret;

	addr = addr_alarm_sec[rtc->alarm];
	ret = lp8788_read_multi_bytes(lp, addr, data, LPTIME_MAX);
	if (ret)
		return ret;

	tm->tm_sec  = data[LPTIME_SEC];
	tm->tm_min  = data[LPTIME_MIN];
	tm->tm_hour = data[LPTIME_HOUR];
	tm->tm_mday = data[LPTIME_MDAY];
	tm->tm_mon  = data[LPTIME_MON] - LP8788_MONTH_OFFSET;
	tm->tm_year = data[LPTIME_YEAR] + LP8788_BASE_YEAR - 1900;
	tm->tm_wday = _to_tm_wday(data[LPTIME_WDAY]);
	alarm->enabled = data[LPTIME_WDAY] & LP8788_ALM_EN_M;

	return 0;
}
