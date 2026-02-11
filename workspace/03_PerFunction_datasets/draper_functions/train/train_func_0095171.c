hmc5843_show_scale_avail(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct hmc5843_data *data = iio_priv(dev_to_iio_dev(dev));

	size_t len = 0;
	int i;

	for (i = 0; i < data->variant->n_regval_to_nanoscale; i++)
		len += scnprintf(buf + len, PAGE_SIZE - len,
			"0.%09d ", data->variant->regval_to_nanoscale[i]);


	buf[len - 1] = '\n';

	return len;
}
