st_accel_common_probe(struct iio_dev *indio_dev)
{
	struct st_sensor_data *adata = iio_priv(indio_dev);
	struct st_sensors_platform_data *pdata =
		(struct st_sensors_platform_data *)adata->dev->platform_data;
	int irq = adata->get_irq_data_ready(indio_dev);
	int err;

	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &accel_info;
	mutex_init(&adata->tb.buf_lock);

	err = st_sensors_power_enable(indio_dev);
	if (err)
		return err;

	err = st_sensors_check_device_support(indio_dev,
					ARRAY_SIZE(st_accel_sensors_settings),
					st_accel_sensors_settings);
	if (err < 0)
		goto st_accel_power_off;

	adata->num_data_channels = ST_ACCEL_NUMBER_DATA_CHANNELS;
	adata->multiread_bit = adata->sensor_settings->multi_read_bit;
	indio_dev->channels = adata->sensor_settings->ch;
	indio_dev->num_channels = ST_SENSORS_NUMBER_ALL_CHANNELS;

	adata->current_fullscale = (struct st_sensor_fullscale_avl *)
					&adata->sensor_settings->fs.fs_avl[0];
	adata->odr = adata->sensor_settings->odr.odr_avl[0].hz;

	if (!pdata)
		pdata = (struct st_sensors_platform_data *)&default_accel_pdata;

	err = st_sensors_init_sensor(indio_dev, adata->dev->platform_data);
	if (err < 0)
		goto st_accel_power_off;

	err = st_accel_allocate_ring(indio_dev);
	if (err < 0)
		goto st_accel_power_off;

	if (irq > 0) {
		err = st_sensors_allocate_trigger(indio_dev,
						 ST_ACCEL_TRIGGER_OPS);
		if (err < 0)
			goto st_accel_probe_trigger_error;
	}

	err = iio_device_register(indio_dev);
	if (err)
		goto st_accel_device_register_error;

	dev_info(&indio_dev->dev, "registered accelerometer %s\n",
		 indio_dev->name);

	return 0;

st_accel_device_register_error:
	if (irq > 0)
		st_sensors_deallocate_trigger(indio_dev);
st_accel_probe_trigger_error:
	st_accel_deallocate_ring(indio_dev);
st_accel_power_off:
	st_sensors_power_disable(indio_dev);

	return err;
}
