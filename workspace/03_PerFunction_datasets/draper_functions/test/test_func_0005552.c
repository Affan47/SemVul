pm8xxx_alarm_trigger(int irq, void *dev_id)
{
	struct pm8xxx_rtc *rtc_dd = dev_id;
	const struct pm8xxx_rtc_regs *regs = rtc_dd->regs;
	unsigned int ctrl_reg;
	int rc;
	unsigned long irq_flags;

	rtc_update_irq(rtc_dd->rtc, 1, RTC_IRQF | RTC_AF);

	spin_lock_irqsave(&rtc_dd->ctrl_reg_lock, irq_flags);


	rc = regmap_read(rtc_dd->regmap, regs->alarm_ctrl, &ctrl_reg);
	if (rc) {
		spin_unlock_irqrestore(&rtc_dd->ctrl_reg_lock, irq_flags);
		goto rtc_alarm_handled;
	}

	ctrl_reg &= ~regs->alarm_en;

	rc = regmap_write(rtc_dd->regmap, regs->alarm_ctrl, ctrl_reg);
	if (rc) {
		spin_unlock_irqrestore(&rtc_dd->ctrl_reg_lock, irq_flags);
		dev_err(rtc_dd->rtc_dev,
			"Write to alarm control register failed\n");
		goto rtc_alarm_handled;
	}

	spin_unlock_irqrestore(&rtc_dd->ctrl_reg_lock, irq_flags);


	rc = regmap_read(rtc_dd->regmap, regs->alarm_ctrl2, &ctrl_reg);
	if (rc) {
		dev_err(rtc_dd->rtc_dev,
			"RTC Alarm control2 register read failed\n");
		goto rtc_alarm_handled;
	}

	ctrl_reg |= PM8xxx_RTC_ALARM_CLEAR;
	rc = regmap_write(rtc_dd->regmap, regs->alarm_ctrl2, ctrl_reg);
	if (rc)
		dev_err(rtc_dd->rtc_dev,
			"Write to RTC Alarm control2 register failed\n");

rtc_alarm_handled:
	return IRQ_HANDLED;
}
