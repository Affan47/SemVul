iio_buffer_store_enable(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf,
				       size_t len)
{
	int ret;
	bool requested_state;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	bool inlist;

	ret = strtobool(buf, &requested_state);
	if (ret < 0)
		return ret;

	mutex_lock(&indio_dev->mlock);


	inlist = iio_buffer_is_active(indio_dev->buffer);

	if (inlist == requested_state)
		goto done;

	if (requested_state)
		ret = __iio_update_buffers(indio_dev,
					 indio_dev->buffer, NULL);
	else
		ret = __iio_update_buffers(indio_dev,
					 NULL, indio_dev->buffer);

done:
	mutex_unlock(&indio_dev->mlock);
	return (ret < 0) ? ret : len;
}
