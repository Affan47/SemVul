governor_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	if (!to_devfreq(dev)->governor)
		return -EINVAL;

	return sprintf(buf, "%s\n", to_devfreq(dev)->governor->name);
}
