iio_buffer_poll(struct file *filp,
			     struct poll_table_struct *wait)
{
	struct iio_dev *indio_dev = filp->private_data;
	struct iio_buffer *rb = indio_dev->buffer;

	if (!indio_dev->info)
		return 0;

	poll_wait(filp, &rb->pollq, wait);
	if (iio_buffer_ready(indio_dev, rb, rb->watermark, 0))
		return POLLIN | POLLRDNORM;
	return 0;
}
