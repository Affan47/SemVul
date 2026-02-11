show_label(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	static const char * const labels[] = {
		"+5V",
		"5VSB",
		"Vbat",
	};
	static const char * const labels_it8721[] = {
		"+3.3V",
		"3VSB",
		"Vbat",
	};
	struct it87_data *data = dev_get_drvdata(dev);
	int nr = to_sensor_dev_attr(attr)->index;
	const char *label;

	if (has_12mv_adc(data) || has_10_9mv_adc(data))
		label = labels_it8721[nr];
	else
		label = labels[nr];

	return sprintf(buf, "%s\n", label);
}
