xadc_handle_events(struct iio_dev *indio_dev, unsigned long events)
{
	unsigned int i;

	for_each_set_bit(i, &events, 8)
		xadc_handle_event(indio_dev, i);
}
