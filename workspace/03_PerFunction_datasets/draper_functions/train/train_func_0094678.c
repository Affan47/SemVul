adis16260_stop_device(struct iio_dev *indio_dev)
{
	struct adis16260 *adis16260 = iio_priv(indio_dev);
	int ret;
	u16 val = ADIS16260_SLP_CNT_POWER_OFF;

	ret = adis_write_reg_16(&adis16260->adis, ADIS16260_SLP_CNT, val);
	if (ret)
		dev_err(&indio_dev->dev, "problem with turning device off: SLP_CNT");

	return ret;
}
