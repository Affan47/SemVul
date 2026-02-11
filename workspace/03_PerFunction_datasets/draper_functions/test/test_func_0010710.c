adis16060_w_probe(struct spi_device *spi)
{
	int ret;
	struct iio_dev *indio_dev = adis16060_iio_dev;
	struct adis16060_state *st;

	if (!indio_dev) {
		ret =  -ENODEV;
		goto error_ret;
	}
	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);
	st->us_w = spi;
	return 0;

error_ret:
	return ret;
}
