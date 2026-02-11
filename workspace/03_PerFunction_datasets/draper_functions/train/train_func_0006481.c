ad5764_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = spi_get_drvdata(spi);
	struct ad5764_state *st = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	if (st->chip_info->int_vref == 0)
		regulator_bulk_disable(ARRAY_SIZE(st->vref_reg), st->vref_reg);

	return 0;
}
