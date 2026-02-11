ad5933_show(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad5933_state *st = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int ret = 0, len = 0;

	mutex_lock(&indio_dev->mlock);
	switch ((u32) this_attr->address) {
	case AD5933_OUT_RANGE:
		len = sprintf(buf, "%u\n",
			      st->range_avail[(st->ctrl_hb >> 1) & 0x3]);
		break;
	case AD5933_OUT_RANGE_AVAIL:
		len = sprintf(buf, "%u %u %u %u\n", st->range_avail[0],
			      st->range_avail[3], st->range_avail[2],
			      st->range_avail[1]);
		break;
	case AD5933_OUT_SETTLING_CYCLES:
		len = sprintf(buf, "%d\n", st->settling_cycles);
		break;
	case AD5933_IN_PGA_GAIN:
		len = sprintf(buf, "%s\n",
			      (st->ctrl_hb & AD5933_CTRL_PGA_GAIN_1) ?
			      "1" : "0.2");
		break;
	case AD5933_IN_PGA_GAIN_AVAIL:
		len = sprintf(buf, "1 0.2\n");
		break;
	case AD5933_FREQ_POINTS:
		len = sprintf(buf, "%d\n", st->freq_points);
		break;
	default:
		ret = -EINVAL;
	}

	mutex_unlock(&indio_dev->mlock);
	return ret ? ret : len;
}
