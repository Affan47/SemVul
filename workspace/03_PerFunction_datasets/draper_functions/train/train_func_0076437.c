ad7280_write_channel_config(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf,
					   size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7280_state *st = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	long val;
	int ret;

	ret = kstrtol(buf, 10, &val);
	if (ret)
		return ret;

	switch ((u32)this_attr->address) {
	case AD7280A_CELL_OVERVOLTAGE:
	case AD7280A_CELL_UNDERVOLTAGE:
		val = ((val - 1000) * 100) / 1568;
		break;
	case AD7280A_AUX_ADC_OVERVOLTAGE:
	case AD7280A_AUX_ADC_UNDERVOLTAGE:
		val = (val * 10) / 196;
		break;
	default:
		return -EFAULT;
	}

	val = clamp(val, 0L, 0xFFL);

	mutex_lock(&indio_dev->mlock);
	switch ((u32)this_attr->address) {
	case AD7280A_CELL_OVERVOLTAGE:
		st->cell_threshhigh = val;
		break;
	case AD7280A_CELL_UNDERVOLTAGE:
		st->cell_threshlow = val;
		break;
	case AD7280A_AUX_ADC_OVERVOLTAGE:
		st->aux_threshhigh = val;
		break;
	case AD7280A_AUX_ADC_UNDERVOLTAGE:
		st->aux_threshlow = val;
		break;
	}

	ret = ad7280_write(st, AD7280A_DEVADDR_MASTER,
			   this_attr->address, 1, val);

	mutex_unlock(&indio_dev->mlock);

	return ret ? ret : len;
}
