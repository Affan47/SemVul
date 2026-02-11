apds9960_read_event_config(struct iio_dev *indio_dev,
				      const struct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_direction dir)
{
	struct apds9960_data *data = iio_priv(indio_dev);

	switch (chan->type) {
	case IIO_PROXIMITY:
		return data->pxs_int;
	case IIO_INTENSITY:
		return data->als_int;
	default:
		return -EINVAL;
	}

	return 0;
}
