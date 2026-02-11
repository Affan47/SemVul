ltc4222_show_bool(struct device *dev,
				 struct device_attribute *da, char *buf)
{
	struct sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(da);
	struct regmap *regmap = dev_get_drvdata(dev);
	unsigned int fault;
	int ret;

	ret = regmap_read(regmap, attr->nr, &fault);
	if (ret < 0)
		return ret;
	fault &= attr->index;
	if (fault)
		regmap_update_bits(regmap, attr->nr, attr->index, 0);

	return snprintf(buf, PAGE_SIZE, "%d\n", !!fault);
}
