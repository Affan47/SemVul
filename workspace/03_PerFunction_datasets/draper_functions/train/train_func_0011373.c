lp8788_adc_read_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan,
			int *val, int *val2, long mask)
{
	struct lp8788_adc *adc = iio_priv(indio_dev);
	enum lp8788_adc_id id = chan->channel;
	int ret;

	mutex_lock(&adc->lock);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = lp8788_get_adc_result(adc, id, val) ? -EIO : IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SCALE:
		*val = lp8788_scale[id] / 1000000;
		*val2 = lp8788_scale[id] % 1000000;
		ret = IIO_VAL_INT_PLUS_MICRO;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&adc->lock);

	return ret;
}
