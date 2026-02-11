sca3000_show_rev(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	int len = 0, ret;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct sca3000_state *st = iio_priv(indio_dev);

	mutex_lock(&st->lock);
	ret = sca3000_read_data_short(st, SCA3000_REG_ADDR_REVID, 1);
	if (ret < 0)
		goto error_ret;
	len += sprintf(buf + len,
		       "major=%d, minor=%d\n",
		       st->rx[0] & SCA3000_REVID_MAJOR_MASK,
		       st->rx[0] & SCA3000_REVID_MINOR_MASK);
error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}
