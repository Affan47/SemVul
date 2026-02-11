lp8788_rtc_probe(struct platform_device *pdev)
{
	struct lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	struct lp8788_rtc *rtc;
	struct device *dev = &pdev->dev;

	rtc = devm_kzalloc(dev, sizeof(struct lp8788_rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	rtc->lp = lp;
	rtc->alarm = lp->pdata ? lp->pdata->alarm_sel : DEFAULT_ALARM_SEL;
	platform_set_drvdata(pdev, rtc);

	device_init_wakeup(dev, 1);

	rtc->rdev = devm_rtc_device_register(dev, "lp8788_rtc",
					&lp8788_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc->rdev)) {
		dev_err(dev, "can not register rtc device\n");
		return PTR_ERR(rtc->rdev);
	}

	if (lp8788_alarm_irq_register(pdev, rtc))
		dev_warn(lp->dev, "no rtc irq handler\n");

	return 0;
}
