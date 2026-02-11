tsys01_probe(struct iio_dev *indio_dev, struct device *dev)
{
	int ret;
	struct tsys01_dev *dev_data = iio_priv(indio_dev);

	mutex_init(&dev_data->lock);

	indio_dev->info = &tsys01_info;
	indio_dev->name = dev->driver->name;
	indio_dev->dev.parent = dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = tsys01_channels;
	indio_dev->num_channels = ARRAY_SIZE(tsys01_channels);

	ret = dev_data->reset(dev_data->client, TSYS01_RESET, 3000);
	if (ret)
		return ret;

	ret = tsys01_read_prom(indio_dev);
	if (ret)
		return ret;

	return devm_iio_device_register(dev, indio_dev);
}
