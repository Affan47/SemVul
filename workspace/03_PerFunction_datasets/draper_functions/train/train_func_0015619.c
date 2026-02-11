iio_channel_release_all(struct iio_channel *channels)
{
	struct iio_channel *chan = &channels[0];

	while (chan->indio_dev) {
		iio_device_put(chan->indio_dev);
		chan++;
	}
	kfree(channels);
}
