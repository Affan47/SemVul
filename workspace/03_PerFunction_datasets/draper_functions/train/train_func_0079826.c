pcf50633_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct pcf50633_rtc *rtc = dev_get_drvdata(dev);
	int err;

	if (enabled)
		err = pcf50633_irq_unmask(rtc->pcf, PCF50633_IRQ_ALARM);
	else
		err = pcf50633_irq_mask(rtc->pcf, PCF50633_IRQ_ALARM);

	if (err < 0)
		return err;

	rtc->alarm_enabled = enabled;

	return 0;
}
