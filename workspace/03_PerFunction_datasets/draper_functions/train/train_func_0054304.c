adis_init(struct adis *adis, struct iio_dev *indio_dev,
	struct spi_device *spi, const struct adis_data *data)
{
	mutex_init(&adis->txrx_lock);
	adis->spi = spi;
	adis->data = data;
	iio_device_set_drvdata(indio_dev, adis);

	if (data->has_paging) {

		adis->current_page = -1;
	} else {

		adis->current_page = 0;
	}

	return adis_enable_irq(adis, false);
}
