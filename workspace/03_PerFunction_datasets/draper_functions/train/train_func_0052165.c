st_sensors_read_info_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *ch, int *val)
{
	int err;
	struct st_sensor_data *sdata = iio_priv(indio_dev);

	mutex_lock(&indio_dev->mlock);
	if (indio_dev->currentmode == INDIO_BUFFER_TRIGGERED) {
		err = -EBUSY;
		goto out;
	} else {
		err = st_sensors_set_enable(indio_dev, true);
		if (err < 0)
			goto out;

		msleep((sdata->sensor_settings->bootime * 1000) / sdata->odr);
		err = st_sensors_read_axis_data(indio_dev, ch, val);
		if (err < 0)
			goto out;

		*val = *val >> ch->scan_type.shift;

		err = st_sensors_set_enable(indio_dev, false);
	}
out:
	mutex_unlock(&indio_dev->mlock);

	return err;
}
