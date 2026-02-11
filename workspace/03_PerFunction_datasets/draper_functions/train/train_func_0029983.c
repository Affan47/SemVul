trip_point_hyst_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct thermal_zone_device *tz = to_thermal_zone(dev);
	int trip, ret;
	int temperature;

	if (!tz->ops->set_trip_hyst)
		return -EPERM;

	if (!sscanf(attr->attr.name, "trip_point_%d_hyst", &trip))
		return -EINVAL;

	if (kstrtoint(buf, 10, &temperature))
		return -EINVAL;


	ret = tz->ops->set_trip_hyst(tz, trip, temperature);

	return ret ? ret : count;
}
