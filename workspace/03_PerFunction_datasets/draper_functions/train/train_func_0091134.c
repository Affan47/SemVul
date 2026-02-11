bmc150_accel_set_watermark(struct iio_dev *indio_dev, unsigned val)
{
	struct bmc150_accel_data *data = iio_priv(indio_dev);

	if (val > BMC150_ACCEL_FIFO_LENGTH)
		val = BMC150_ACCEL_FIFO_LENGTH;

	mutex_lock(&data->mutex);
	data->watermark = val;
	mutex_unlock(&data->mutex);

	return 0;
}
