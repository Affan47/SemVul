sx9500_buffer_predisable(struct iio_dev *indio_dev)
{
	struct sx9500_data *data = iio_priv(indio_dev);
	int ret = 0, i;

	iio_triggered_buffer_predisable(indio_dev);

	mutex_lock(&data->mutex);

	for (i = 0; i < SX9500_NUM_CHANNELS; i++)
		if (test_bit(i, indio_dev->active_scan_mask)) {
			ret = sx9500_dec_chan_users(data, i);
			if (ret)
				break;
		}

	if (ret)
		for (i = i - 1; i >= 0; i--)
			if (test_bit(i, indio_dev->active_scan_mask))
				sx9500_inc_chan_users(data, i);

	mutex_unlock(&data->mutex);

	return ret;
}
