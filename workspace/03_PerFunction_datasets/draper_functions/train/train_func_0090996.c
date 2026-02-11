rtl2832_sdr_unset_tuner(struct rtl2832_sdr_dev *dev)
{
	struct platform_device *pdev = dev->pdev;
	struct rtl2832_sdr_platform_data *pdata = pdev->dev.platform_data;
	struct dvb_frontend *fe = pdata->dvb_frontend;

	dev_dbg(&pdev->dev, "\n");

	if (fe->ops.tuner_ops.sleep)
		fe->ops.tuner_ops.sleep(fe);

	return;
}
