st_sensors_set_odr(struct iio_dev *indio_dev, unsigned int odr)
{
	int err;
	struct st_sensor_odr_avl odr_out = {0, 0};
	struct st_sensor_data *sdata = iio_priv(indio_dev);

	err = st_sensors_match_odr(sdata->sensor_settings, odr, &odr_out);
	if (err < 0)
		goto st_sensors_match_odr_error;

	if ((sdata->sensor_settings->odr.addr ==
					sdata->sensor_settings->pw.addr) &&
				(sdata->sensor_settings->odr.mask ==
					sdata->sensor_settings->pw.mask)) {
		if (sdata->enabled == true) {
			err = st_sensors_write_data_with_mask(indio_dev,
				sdata->sensor_settings->odr.addr,
				sdata->sensor_settings->odr.mask,
				odr_out.value);
		} else {
			err = 0;
		}
	} else {
		err = st_sensors_write_data_with_mask(indio_dev,
			sdata->sensor_settings->odr.addr,
			sdata->sensor_settings->odr.mask,
			odr_out.value);
	}
	if (err >= 0)
		sdata->odr = odr_out.hz;

st_sensors_match_odr_error:
	return err;
}
