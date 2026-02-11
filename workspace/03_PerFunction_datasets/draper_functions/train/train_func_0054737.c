ad7291_read_event_config(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir)
{
	struct ad7291_chip_info *chip = iio_priv(indio_dev);


	switch (chan->type) {
	case IIO_VOLTAGE:
		return !!(chip->c_mask & BIT(15 - chan->channel));
	case IIO_TEMP:

		return 1;
	default:
		return -EINVAL;
	}

}
