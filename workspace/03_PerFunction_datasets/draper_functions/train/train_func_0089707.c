ltr501_write_intr_prst(struct ltr501_data *data,
				  enum iio_chan_type type,
				  int val, int val2)
{
	int ret, samp_period, new_val;
	unsigned long period;

	if (val < 0 || val2 < 0)
		return -EINVAL;


	period = ((val * 1000000) + val2);

	switch (type) {
	case IIO_INTENSITY:
		ret = ltr501_als_read_samp_period(data, &samp_period);
		if (ret < 0)
			return ret;


		if (period < samp_period)
			return -EINVAL;

		new_val = DIV_ROUND_UP(period, samp_period);
		if (new_val < 0 || new_val > 0x0f)
			return -EINVAL;

		mutex_lock(&data->lock_als);
		ret = regmap_field_write(data->reg_als_prst, new_val);
		mutex_unlock(&data->lock_als);
		if (ret >= 0)
			data->als_period = period;

		return ret;
	case IIO_PROXIMITY:
		ret = ltr501_ps_read_samp_period(data, &samp_period);
		if (ret < 0)
			return ret;


		if (period < samp_period)
			return -EINVAL;

		new_val = DIV_ROUND_UP(period, samp_period);
		if (new_val < 0 || new_val > 0x0f)
			return -EINVAL;

		mutex_lock(&data->lock_ps);
		ret = regmap_field_write(data->reg_ps_prst, new_val);
		mutex_unlock(&data->lock_ps);
		if (ret >= 0)
			data->ps_period = period;

		return ret;
	default:
		return -EINVAL;
	}

	return -EINVAL;
}
