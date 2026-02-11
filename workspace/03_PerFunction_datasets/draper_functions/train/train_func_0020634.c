adis16400_probe(struct spi_device *spi)
{
	struct adis16400_state *st;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (indio_dev == NULL)
		return -ENOMEM;

	st = iio_priv(indio_dev);

	spi_set_drvdata(spi, indio_dev);


	st->variant = &adis16400_chips[spi_get_device_id(spi)->driver_data];
	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->channels = st->variant->channels;
	indio_dev->num_channels = st->variant->num_channels;
	indio_dev->info = &adis16400_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (!(st->variant->flags & ADIS16400_NO_BURST)) {
		adis16400_setup_chan_mask(st);
		indio_dev->available_scan_masks = st->avail_scan_mask;
	}

	ret = adis_init(&st->adis, indio_dev, spi, &adis16400_data);
	if (ret)
		return ret;

	ret = adis_setup_buffer_and_trigger(&st->adis, indio_dev,
			adis16400_trigger_handler);
	if (ret)
		return ret;


	ret = adis16400_initial_setup(indio_dev);
	if (ret)
		goto error_cleanup_buffer;
	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_cleanup_buffer;

	adis16400_debugfs_init(indio_dev);
	return 0;

error_cleanup_buffer:
	adis_cleanup_buffer_and_trigger(&st->adis, indio_dev);
	return ret;
}
