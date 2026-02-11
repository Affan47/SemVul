ds2781_write_param_eeprom_bin(struct file *filp,
				struct kobject *kobj,
				struct bin_attribute *bin_attr,
				char *buf, loff_t off, size_t count)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	struct power_supply *psy = to_power_supply(dev);
	struct ds2781_device_info *dev_info = to_ds2781_device_info(psy);
	int ret;

	ret = ds2781_write(dev_info, buf,
				DS2781_EEPROM_BLOCK1_START + off, count);
	if (ret < 0)
		return ret;

	ret = ds2781_save_eeprom(dev_info, DS2781_EEPROM_BLOCK1_START);
	if (ret < 0)
		return ret;

	return count;
}
