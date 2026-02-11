ds1286_set_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	struct ds1286_priv *priv = dev_get_drvdata(dev);
	unsigned char hrs, min, sec;

	hrs = alm->time.tm_hour;
	min = alm->time.tm_min;
	sec = alm->time.tm_sec;

	if (hrs >= 24)
		hrs = 0xff;

	if (min >= 60)
		min = 0xff;

	if (sec != 0)
		return -EINVAL;

	min = bin2bcd(min);
	hrs = bin2bcd(hrs);

	spin_lock(&priv->lock);
	ds1286_rtc_write(priv, hrs, RTC_HOURS_ALARM);
	ds1286_rtc_write(priv, min, RTC_MINUTES_ALARM);
	spin_unlock(&priv->lock);

	return 0;
}
