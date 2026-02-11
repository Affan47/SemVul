max517_write_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long mask)
{
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = max517_set_value(indio_dev, val, chan->channel);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}
