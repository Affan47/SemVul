ade7758_ring_preenable(struct iio_dev *indio_dev)
{
	unsigned channel;

	if (bitmap_empty(indio_dev->active_scan_mask, indio_dev->masklength))
		return -EINVAL;

	channel = find_first_bit(indio_dev->active_scan_mask,
				 indio_dev->masklength);

	ade7758_write_waveform_type(&indio_dev->dev,
		indio_dev->channels[channel].address);

	return 0;
}
