mxs_lradc_write_raw(struct iio_dev *iio_dev,
			       const struct iio_chan_spec *chan,
			       int val, int val2, long m)
{
	struct mxs_lradc *lradc = iio_priv(iio_dev);
	struct mxs_lradc_scale *scale_avail =
			lradc->scale_avail[chan->channel];
	int ret;

	ret = mutex_trylock(&lradc->lock);
	if (!ret)
		return -EBUSY;

	switch (m) {
	case IIO_CHAN_INFO_SCALE:
		ret = -EINVAL;
		if (val == scale_avail[MXS_LRADC_DIV_DISABLED].integer &&
		    val2 == scale_avail[MXS_LRADC_DIV_DISABLED].nano) {

			clear_bit(chan->channel, &lradc->is_divided);
			ret = 0;
		} else if (val == scale_avail[MXS_LRADC_DIV_ENABLED].integer &&
			   val2 == scale_avail[MXS_LRADC_DIV_ENABLED].nano) {

			set_bit(chan->channel, &lradc->is_divided);
			ret = 0;
		}

		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&lradc->lock);

	return ret;
}
