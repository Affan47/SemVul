stk8312_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct stk8312_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (iio_buffer_enabled(indio_dev))
			return -EBUSY;
		mutex_lock(&data->lock);
		ret = stk8312_set_mode(data, data->mode | STK8312_MODE_ACTIVE);
		if (ret < 0) {
			mutex_unlock(&data->lock);
			return ret;
		}
		ret = stk8312_read_accel(data, chan->address);
		if (ret < 0) {
			stk8312_set_mode(data,
					 data->mode & (~STK8312_MODE_ACTIVE));
			mutex_unlock(&data->lock);
			return ret;
		}
		*val = sign_extend32(ret, 7);
		ret = stk8312_set_mode(data,
				       data->mode & (~STK8312_MODE_ACTIVE));
		mutex_unlock(&data->lock);
		if (ret < 0)
			return ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = stk8312_scale_table[data->range - 1][0];
		*val2 = stk8312_scale_table[data->range - 1][1];
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = stk8312_samp_freq_table[data->sample_rate_idx].val;
		*val2 = stk8312_samp_freq_table[data->sample_rate_idx].val2;
		return IIO_VAL_INT_PLUS_MICRO;
	}

	return -EINVAL;
}
