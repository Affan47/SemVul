adis16480_set_freq(struct iio_dev *indio_dev, int val, int val2)
{
	struct adis16480 *st = iio_priv(indio_dev);
	unsigned int t;

	t =  val * 1000 + val2 / 1000;
	if (t <= 0)
		return -EINVAL;

	t = 2460000 / t;
	if (t > 2048)
		t = 2048;

	if (t != 0)
		t--;

	return adis_write_reg_16(&st->adis, ADIS16480_REG_DEC_RATE, t);
}
