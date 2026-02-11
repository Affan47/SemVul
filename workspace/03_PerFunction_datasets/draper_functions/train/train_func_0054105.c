thermal_cooling_device_cur_state_show(struct device *dev,
				      struct device_attribute *attr, char *buf)
{
	struct thermal_cooling_device *cdev = to_cooling_device(dev);
	unsigned long state;
	int ret;

	ret = cdev->ops->get_cur_state(cdev, &state);
	if (ret)
		return ret;
	return sprintf(buf, "%ld\n", state);
}
