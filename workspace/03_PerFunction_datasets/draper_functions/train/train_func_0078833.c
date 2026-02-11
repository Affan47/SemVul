ad5360_alloc_channels(struct iio_dev *indio_dev)
{
	struct ad5360_state *st = iio_priv(indio_dev);
	struct iio_chan_spec *channels;
	unsigned int i;

	channels = kcalloc(st->chip_info->num_channels,
			   sizeof(struct iio_chan_spec), GFP_KERNEL);

	if (!channels)
		return -ENOMEM;

	for (i = 0; i < st->chip_info->num_channels; ++i) {
		channels[i] = st->chip_info->channel_template;
		channels[i].channel = i;
		channels[i].address = AD5360_CHAN_ADDR(i);
	}

	indio_dev->channels = channels;

	return 0;
}
