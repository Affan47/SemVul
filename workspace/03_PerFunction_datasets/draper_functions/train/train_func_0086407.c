adis16136_write_raw(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, int val, int val2, long info)
{
	struct adis16136 *adis16136 = iio_priv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_CALIBBIAS:
		return adis_write_reg_32(&adis16136->adis,
			ADIS16136_REG_GYRO_OFF2, val);
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		return adis16136_set_filter(indio_dev, val);
	default:
		break;
	}

	return -EINVAL;
}
