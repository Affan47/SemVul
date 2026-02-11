mc13xxx_rtc_probe(struct platform_device *pdev)
{
	int ret;
	struct mc13xxx_rtc *priv;
	struct mc13xxx *mc13xxx;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mc13xxx = dev_get_drvdata(pdev->dev.parent);
	priv->mc13xxx = mc13xxx;
	priv->valid = 1;

	platform_set_drvdata(pdev, priv);

	mc13xxx_lock(mc13xxx);

	mc13xxx_irq_ack(mc13xxx, MC13XXX_IRQ_RTCRST);

	ret = mc13xxx_irq_request(mc13xxx, MC13XXX_IRQ_RTCRST,
			mc13xxx_rtc_reset_handler, DRIVER_NAME, priv);
	if (ret)
		goto err_irq_request;

	ret = mc13xxx_irq_request(mc13xxx, MC13XXX_IRQ_1HZ,
			mc13xxx_rtc_update_handler, DRIVER_NAME, priv);
	if (ret)
		goto err_irq_request;

	ret = mc13xxx_irq_request_nounmask(mc13xxx, MC13XXX_IRQ_TODA,
			mc13xxx_rtc_alarm_handler, DRIVER_NAME, priv);
	if (ret)
		goto err_irq_request;

	mc13xxx_unlock(mc13xxx);

	priv->rtc = devm_rtc_device_register(&pdev->dev, pdev->name,
					     &mc13xxx_rtc_ops, THIS_MODULE);

	return 0;

err_irq_request:
	mc13xxx_irq_free(mc13xxx, MC13XXX_IRQ_TODA, priv);
	mc13xxx_irq_free(mc13xxx, MC13XXX_IRQ_1HZ, priv);
	mc13xxx_irq_free(mc13xxx, MC13XXX_IRQ_RTCRST, priv);

	mc13xxx_unlock(mc13xxx);

	return ret;
}
