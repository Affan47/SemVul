st_press_common_probe(struct iio_dev *indio_dev)
{
	struct st_sensor_data *press_data = iio_priv(indio_dev);
	struct st_sensors_platform_data *pdata =
		(struct st_sensors_platform_data *)press_data->dev->platform_data;
	int irq = press_data->get_irq_data_ready(indio_dev);
	int err;

	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &press_info;
	mutex_init(&press_data->tb.buf_lock);

	err = st_sensors_power_enable(indio_dev);
	if (err)
		return err;

	err = st_sensors_check_device_support(indio_dev,
					ARRAY_SIZE(st_press_sensors_settings),
					st_press_sensors_settings);
	if (err < 0)
		goto st_press_power_off;


	press_data->num_data_channels = press_data->sensor_settings->num_ch - 1;
	press_data->multiread_bit = press_data->sensor_settings->multi_read_bit;
	indio_dev->channels = press_data->sensor_settings->ch;
	indio_dev->num_channels = press_data->sensor_settings->num_ch;

	press_data->current_fullscale =
		(struct st_sensor_fullscale_avl *)
			&press_data->sensor_settings->fs.fs_avl[0];

	press_data->odr = press_data->sensor_settings->odr.odr_avl[0].hz;


	if (!pdata && press_data->sensor_settings->drdy_irq.addr)
		pdata =	(struct st_sensors_platform_data *)&default_press_pdata;

	err = st_sensors_init_sensor(indio_dev, press_data->dev->platform_data);
	if (err < 0)
		goto st_press_power_off;

	err = st_press_allocate_ring(indio_dev);
	if (err < 0)
		goto st_press_power_off;

	if (irq > 0) {
		err = st_sensors_allocate_trigger(indio_dev,
						  ST_PRESS_TRIGGER_OPS);
		if (err < 0)
			goto st_press_probe_trigger_error;
	}

	err = iio_device_register(indio_dev);
	if (err)
		goto st_press_device_register_error;

	dev_info(&indio_dev->dev, "registered pressure sensor %s\n",
		 indio_dev->name);

	return err;

st_press_device_register_error:
	if (irq > 0)
		st_sensors_deallocate_trigger(indio_dev);
st_press_probe_trigger_error:
	st_press_deallocate_ring(indio_dev);
st_press_power_off:
	st_sensors_power_disable(indio_dev);

	return err;
}
