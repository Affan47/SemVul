adis16400_write_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long info)
{
	struct adis16400_state *st = iio_priv(indio_dev);
	int ret, sps;

	switch (info) {
	case IIO_CHAN_INFO_CALIBBIAS:
		mutex_lock(&indio_dev->mlock);
		ret = adis_write_reg_16(&st->adis,
				adis16400_addresses[chan->scan_index], val);
		mutex_unlock(&indio_dev->mlock);
		return ret;
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:


		mutex_lock(&indio_dev->mlock);
		st->filt_int = val;

		sps = st->variant->get_freq(st);
		if (sps < 0) {
			mutex_unlock(&indio_dev->mlock);
			return sps;
		}

		ret = adis16400_set_filter(indio_dev, sps,
			val * 1000 + val2 / 1000);
		mutex_unlock(&indio_dev->mlock);
		return ret;
	case IIO_CHAN_INFO_SAMP_FREQ:
		sps = val * 1000 + val2 / 1000;

		if (sps <= 0)
			return -EINVAL;

		mutex_lock(&indio_dev->mlock);
		ret = st->variant->set_freq(st, sps);
		mutex_unlock(&indio_dev->mlock);
		return ret;
	default:
		return -EINVAL;
	}
}
