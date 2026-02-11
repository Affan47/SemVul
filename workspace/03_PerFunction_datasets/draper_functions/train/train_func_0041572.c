ad5791_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val,
			    int val2,
			    long mask)
{
	struct ad5791_state *st = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		val &= GENMASK(chan->scan_type.realbits - 1, 0);
		val <<= chan->scan_type.shift;

		return ad5791_spi_write(st, chan->address, val);

	default:
		return -EINVAL;
	}
}
