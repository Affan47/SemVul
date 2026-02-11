asus_hwmon_temp1(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	struct asus_wmi *asus = dev_get_drvdata(dev);
	u32 value;
	int err;

	err = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_THERMAL_CTRL, &value);

	if (err < 0)
		return err;

	value = DECI_KELVIN_TO_CELSIUS((value & 0xFFFF)) * 1000;

	return sprintf(buf, "%d\n", value);
}
