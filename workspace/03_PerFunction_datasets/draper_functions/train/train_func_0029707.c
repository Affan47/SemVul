iio_enum_read(struct iio_dev *indio_dev,
	uintptr_t priv, const struct iio_chan_spec *chan, char *buf)
{
	const struct iio_enum *e = (const struct iio_enum *)priv;
	int i;

	if (!e->get)
		return -EINVAL;

	i = e->get(indio_dev, chan);
	if (i < 0)
		return i;
	else if (i >= e->num_items)
		return -EINVAL;

	return snprintf(buf, PAGE_SIZE, "%s\n", e->items[i]);
}
