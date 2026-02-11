pm8xxx_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	int rc, i;
	u8 value[NUM_8_BIT_RTC_REGS];
	unsigned int ctrl_reg;
	unsigned long secs, irq_flags;
	struct pm8xxx_rtc *rtc_dd = dev_get_drvdata(dev);
	const struct pm8xxx_rtc_regs *regs = rtc_dd->regs;

	rtc_tm_to_time(&alarm->time, &secs);

	for (i = 0; i < NUM_8_BIT_RTC_REGS; i++) {
		value[i] = secs & 0xFF;
		secs >>= 8;
	}

	spin_lock_irqsave(&rtc_dd->ctrl_reg_lock, irq_flags);

	rc = regmap_bulk_write(rtc_dd->regmap, regs->alarm_rw, value,
			       sizeof(value));
	if (rc) {
		dev_err(dev, "Write to RTC ALARM register failed\n");
		goto rtc_rw_fail;
	}

	rc = regmap_read(rtc_dd->regmap, regs->alarm_ctrl, &ctrl_reg);
	if (rc)
		goto rtc_rw_fail;

	if (alarm->enabled)
		ctrl_reg |= regs->alarm_en;
	else
		ctrl_reg &= ~regs->alarm_en;

	rc = regmap_write(rtc_dd->regmap, regs->alarm_ctrl, ctrl_reg);
	if (rc) {
		dev_err(dev, "Write to RTC alarm control register failed\n");
		goto rtc_rw_fail;
	}

	dev_dbg(dev, "Alarm Set for h:r:s=%d:%d:%d, d/m/y=%d/%d/%d\n",
		alarm->time.tm_hour, alarm->time.tm_min,
		alarm->time.tm_sec, alarm->time.tm_mday,
		alarm->time.tm_mon, alarm->time.tm_year);
rtc_rw_fail:
	spin_unlock_irqrestore(&rtc_dd->ctrl_reg_lock, irq_flags);
	return rc;
}
