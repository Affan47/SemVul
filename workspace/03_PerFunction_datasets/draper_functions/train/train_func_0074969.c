max8997_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct max8997_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	int ret;

	ret = max8997_rtc_tm_to_data(&alrm->time, data);
	if (ret < 0)
		return ret;

	dev_info(info->dev, "%s: %d-%02d-%02d %02d:%02d:%02d\n", __func__,
			data[RTC_YEAR] + 2000, data[RTC_MONTH], data[RTC_DATE],
			data[RTC_HOUR], data[RTC_MIN], data[RTC_SEC]);

	mutex_lock(&info->lock);

	ret = max8997_rtc_stop_alarm(info);
	if (ret < 0)
		goto out;

	ret = max8997_bulk_write(info->rtc, MAX8997_RTC_ALARM1_SEC, RTC_NR_TIME,
				data);
	if (ret < 0) {
		dev_err(info->dev, "%s: fail to write alarm reg(%d)\n",
				__func__, ret);
		goto out;
	}

	ret = max8997_rtc_set_update_reg(info);
	if (ret < 0)
		goto out;

	if (alrm->enabled)
		ret = max8997_rtc_start_alarm(info);
out:
	mutex_unlock(&info->lock);
	return ret;
}
