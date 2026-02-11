st_press_common_remove(struct iio_dev *indio_dev)
{
	struct st_sensor_data *press_data = iio_priv(indio_dev);

	st_sensors_power_disable(indio_dev);

	iio_device_unregister(indio_dev);
	if (press_data->get_irq_data_ready(indio_dev) > 0)
		st_sensors_deallocate_trigger(indio_dev);

	st_press_deallocate_ring(indio_dev);
}
