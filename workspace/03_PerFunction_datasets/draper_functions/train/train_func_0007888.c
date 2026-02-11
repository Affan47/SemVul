mcp4725_write_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val, int val2, long mask)
{
	struct mcp4725_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = mcp4725_set_value(indio_dev, val);
		data->dac_value = val;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}
