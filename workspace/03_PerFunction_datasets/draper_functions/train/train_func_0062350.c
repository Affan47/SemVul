m48t59_rtc_interrupt(int irq, void *dev_id)
{
	struct device *dev = (struct device *)dev_id;
	struct platform_device *pdev = to_platform_device(dev);
	struct m48t59_plat_data *pdata = dev_get_platdata(&pdev->dev);
	struct m48t59_private *m48t59 = platform_get_drvdata(pdev);
	u8 event;

	spin_lock(&m48t59->lock);
	event = M48T59_READ(M48T59_FLAGS);
	spin_unlock(&m48t59->lock);

	if (event & M48T59_FLAGS_AF) {
		rtc_update_irq(m48t59->rtc, 1, (RTC_AF | RTC_IRQF));
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}
