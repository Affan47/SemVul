st_gyro_buffer_postenable(struct iio_dev *indio_dev)
{
	int err;
	struct st_sensor_data *gdata = iio_priv(indio_dev);

	gdata->buffer_data = kmalloc(indio_dev->scan_bytes, GFP_KERNEL);
	if (gdata->buffer_data == NULL) {
		err = -ENOMEM;
		goto allocate_memory_error;
	}

	err = st_sensors_set_axis_enable(indio_dev,
					(u8)indio_dev->active_scan_mask[0]);
	if (err < 0)
		goto st_gyro_buffer_postenable_error;

	err = iio_triggered_buffer_postenable(indio_dev);
	if (err < 0)
		goto st_gyro_buffer_postenable_error;

	return err;

st_gyro_buffer_postenable_error:
	kfree(gdata->buffer_data);
allocate_memory_error:
	return err;
}
