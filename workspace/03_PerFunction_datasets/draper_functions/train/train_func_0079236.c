sca3000_set_ring_int(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf,
				    size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct sca3000_state *st = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	u8 val;
	int ret;

	mutex_lock(&st->lock);
	ret = kstrtou8(buf, 10, &val);
	if (ret)
		goto error_ret;
	ret = sca3000_read_data_short(st, SCA3000_REG_ADDR_INT_MASK, 1);
	if (ret)
		goto error_ret;
	if (val)
		ret = sca3000_write_reg(st,
					SCA3000_REG_ADDR_INT_MASK,
					st->rx[0] | this_attr->address);
	else
		ret = sca3000_write_reg(st,
					SCA3000_REG_ADDR_INT_MASK,
					st->rx[0] & ~this_attr->address);
error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}
