show_als(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	int value = hp_wmi_als_state();
	if (value < 0)
		return -EINVAL;
	return sprintf(buf, "%d\n", value);
}
