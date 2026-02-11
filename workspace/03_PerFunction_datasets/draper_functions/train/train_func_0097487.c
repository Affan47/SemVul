max8907_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct max8907_rtc *rtc = dev_get_drvdata(dev);
	u8 regs[TIME_NUM];
	int ret;

	ret = regmap_bulk_read(rtc->regmap, MAX8907_REG_RTC_SEC, regs,
			       TIME_NUM);
	if (ret < 0)
		return ret;

	regs_to_tm(regs, tm);

	return 0;
}
