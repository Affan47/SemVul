ltr501_write_thresh(struct iio_dev *indio_dev,
			       const struct iio_chan_spec *chan,
			       enum iio_event_type type,
			       enum iio_event_direction dir,
			       enum iio_event_info info,
			       int val, int val2)
{
	struct ltr501_data *data = iio_priv(indio_dev);
	int ret;

	if (val < 0)
		return -EINVAL;

	switch (chan->type) {
	case IIO_INTENSITY:
		if (val > LTR501_ALS_THRESH_MASK)
			return -EINVAL;
		switch (dir) {
		case IIO_EV_DIR_RISING:
			mutex_lock(&data->lock_als);
			ret = regmap_bulk_write(data->regmap,
						LTR501_ALS_THRESH_UP,
						&val, 2);
			mutex_unlock(&data->lock_als);
			return ret;
		case IIO_EV_DIR_FALLING:
			mutex_lock(&data->lock_als);
			ret = regmap_bulk_write(data->regmap,
						LTR501_ALS_THRESH_LOW,
						&val, 2);
			mutex_unlock(&data->lock_als);
			return ret;
		default:
			return -EINVAL;
		}
	case IIO_PROXIMITY:
		if (val > LTR501_PS_THRESH_MASK)
			return -EINVAL;
		switch (dir) {
		case IIO_EV_DIR_RISING:
			mutex_lock(&data->lock_ps);
			ret = regmap_bulk_write(data->regmap,
						LTR501_PS_THRESH_UP,
						&val, 2);
			mutex_unlock(&data->lock_ps);
			return ret;
		case IIO_EV_DIR_FALLING:
			mutex_lock(&data->lock_ps);
			ret = regmap_bulk_write(data->regmap,
						LTR501_PS_THRESH_LOW,
						&val, 2);
			mutex_unlock(&data->lock_ps);
			return ret;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}

	return -EINVAL;
}
