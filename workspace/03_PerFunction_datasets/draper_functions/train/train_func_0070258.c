tps80031_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	u8 buff[TPS80031_RTC_ALARM_NUM_REGS];
	int ret;

	buff[0] = bin2bcd(alrm->time.tm_sec);
	buff[1] = bin2bcd(alrm->time.tm_min);
	buff[2] = bin2bcd(alrm->time.tm_hour);
	buff[3] = bin2bcd(alrm->time.tm_mday);
	buff[4] = bin2bcd(alrm->time.tm_mon + 1);
	buff[5] = bin2bcd(alrm->time.tm_year % RTC_YEAR_OFFSET);
	ret = tps80031_writes(dev->parent, TPS80031_SLAVE_ID1,
			TPS80031_ALARM_SECONDS_REG,
			TPS80031_RTC_ALARM_NUM_REGS, buff);
	if (ret < 0) {
		dev_err(dev, "Writing RTC_ALARM failed, err %d\n", ret);
		return ret;
	}
	return tps80031_rtc_alarm_irq_enable(dev, alrm->enabled);
}
