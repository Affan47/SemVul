bmc150_magn_trig_try_reen(struct iio_trigger *trig)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct bmc150_magn_data *data = iio_priv(indio_dev);
	int ret;

	if (!data->dready_trigger_on)
		return 0;

	mutex_lock(&data->mutex);
	ret = bmc150_magn_reset_intr(data);
	mutex_unlock(&data->mutex);

	return ret;
}
