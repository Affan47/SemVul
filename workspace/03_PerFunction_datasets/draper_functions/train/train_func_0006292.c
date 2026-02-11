sustainable_power_show(struct device *dev, struct device_attribute *devattr,
		       char *buf)
{
	struct thermal_zone_device *tz = to_thermal_zone(dev);

	if (tz->tzp)
		return sprintf(buf, "%u\n", tz->tzp->sustainable_power);
	else
		return -EIO;
}
