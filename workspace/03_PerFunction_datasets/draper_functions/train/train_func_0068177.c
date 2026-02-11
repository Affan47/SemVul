ds2781_set_rsgain_setting(struct device *dev,
	struct device_attribute *attr,
	const char *buf,
	size_t count)
{
	int ret;
	u16 new_setting;
	struct power_supply *psy = to_power_supply(dev);
	struct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	ret = kstrtou16(buf, 0, &new_setting);
	if (ret < 0)
		return ret;


	if (new_setting > 1999) {
		dev_err(dev_info->dev, "Invalid rsgain setting (0 - 1999)\n");
		return -EINVAL;
	}

	ret = ds2781_set_rsgain_register(dev_info, new_setting);
	if (ret < 0)
		return ret;

	return count;
}
