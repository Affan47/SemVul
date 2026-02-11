adis16204_write_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val,
			       int val2,
			       long mask)
{
	struct adis *st = iio_priv(indio_dev);
	int bits;
	s16 val16;
	u8 addr;

	switch (mask) {
	case IIO_CHAN_INFO_CALIBBIAS:
		switch (chan->type) {
		case IIO_ACCEL:
			bits = 12;
			break;
		default:
			return -EINVAL;
		}
		val16 = val & ((1 << bits) - 1);
		addr = adis16204_addresses[chan->scan_index][1];
		return adis_write_reg_16(st, addr, val16);
	}
	return -EINVAL;
}
