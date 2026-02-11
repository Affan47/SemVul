m48t59_rtc_setalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct m48t59_plat_data *pdata = dev_get_platdata(&pdev->dev);
	struct m48t59_private *m48t59 = platform_get_drvdata(pdev);
	struct rtc_time *tm = &alrm->time;
	u8 mday, hour, min, sec;
	unsigned long flags;
	int year = tm->tm_year;

#ifdef CONFIG_SPARC

	year -= 68;
#endif


	if (m48t59->irq == NO_IRQ)
		return -EIO;

	if (year < 0)
		return -EINVAL;


	mday = tm->tm_mday;
	mday = (mday >= 1 && mday <= 31) ? bin2bcd(mday) : 0xff;
	if (mday == 0xff)
		mday = M48T59_READ(M48T59_MDAY);

	hour = tm->tm_hour;
	hour = (hour < 24) ? bin2bcd(hour) : 0x00;

	min = tm->tm_min;
	min = (min < 60) ? bin2bcd(min) : 0x00;

	sec = tm->tm_sec;
	sec = (sec < 60) ? bin2bcd(sec) : 0x00;

	spin_lock_irqsave(&m48t59->lock, flags);

	M48T59_SET_BITS(M48T59_CNTL_WRITE, M48T59_CNTL);

	M48T59_WRITE(mday, M48T59_ALARM_DATE);
	M48T59_WRITE(hour, M48T59_ALARM_HOUR);
	M48T59_WRITE(min, M48T59_ALARM_MIN);
	M48T59_WRITE(sec, M48T59_ALARM_SEC);


	M48T59_CLEAR_BITS(M48T59_CNTL_WRITE, M48T59_CNTL);
	spin_unlock_irqrestore(&m48t59->lock, flags);

	dev_dbg(dev, "RTC set alarm time %04d-%02d-%02d %02d/%02d/%02d\n",
		year + 1900, tm->tm_mon, tm->tm_mday,
		tm->tm_hour, tm->tm_min, tm->tm_sec);
	return 0;
}
