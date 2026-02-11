da9063_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct da9063_compatible_rtc *rtc = dev_get_drvdata(dev);
	const struct da9063_compatible_rtc_regmap *config = rtc->config;
	u8 data[RTC_DATA_LEN];
	int ret;
	unsigned int val;

	data[RTC_SEC] = 0;
	ret = regmap_bulk_read(rtc->regmap,
			       config->rtc_alarm_secs_reg,
			       &data[config->rtc_data_start],
			       config->rtc_alarm_len);
	if (ret < 0)
		return ret;

	da9063_data_to_tm(data, &alrm->time, rtc);

	alrm->enabled = !!(data[RTC_YEAR] & config->rtc_alarm_on_mask);

	ret = regmap_read(rtc->regmap,
			  config->rtc_event_reg,
			  &val);
	if (ret < 0)
		return ret;

	if (val & config->rtc_event_alarm_mask)
		alrm->pending = 1;
	else
		alrm->pending = 0;

	return 0;
}
