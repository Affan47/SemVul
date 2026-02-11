autosuspend_store(struct device *dev,
				 struct device_attribute *attr, const char *buf,
				 size_t count)
{
	int value;

	if (sscanf(buf, "%d", &value) != 1 || value >= INT_MAX/1000 ||
			value <= -INT_MAX/1000)
		return -EINVAL;

	pm_runtime_set_autosuspend_delay(dev, value * 1000);
	return count;
}
