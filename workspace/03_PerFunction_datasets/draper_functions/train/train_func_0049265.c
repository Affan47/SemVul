iio_ev_value_show(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int val, val2, val_arr[2];
	int ret;

	ret = indio_dev->info->read_event_value(indio_dev,
		this_attr->c, iio_ev_attr_type(this_attr),
		iio_ev_attr_dir(this_attr), iio_ev_attr_info(this_attr),
		&val, &val2);
	if (ret < 0)
		return ret;
	val_arr[0] = val;
	val_arr[1] = val2;
	return iio_format_value(buf, ret, 2, val_arr);
}
