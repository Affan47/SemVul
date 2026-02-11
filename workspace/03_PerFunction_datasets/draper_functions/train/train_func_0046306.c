adis16240_spi_read_signed(struct device *dev,
					 struct device_attribute *attr,
					 char *buf,
					 unsigned bits)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct adis *st = iio_priv(indio_dev);
	int ret;
	s16 val = 0;
	unsigned shift = 16 - bits;
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	ret = adis_read_reg_16(st,
			       this_attr->address, (u16 *)&val);
	if (ret)
		return ret;

	if (val & ADIS16240_ERROR_ACTIVE)
		adis_check_status(st);

	val = (s16)(val << shift) >> shift;
	return sprintf(buf, "%d\n", val);
}
