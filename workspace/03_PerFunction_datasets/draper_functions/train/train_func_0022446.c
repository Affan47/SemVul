store_output(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t len)
{
	struct lm3533 *lm3533 = dev_get_drvdata(dev);
	struct lm3533_device_attribute *lattr = to_lm3533_dev_attr(attr);
	int id = lattr->u.output.id;
	u8 val;
	int ret;

	if (kstrtou8(buf, 0, &val))
		return -EINVAL;

	if (lattr->type == LM3533_ATTR_TYPE_BACKLIGHT)
		ret = lm3533_set_hvled_config(lm3533, id, val);
	else
		ret = lm3533_set_lvled_config(lm3533, id, val);

	if (ret)
		return ret;

	return len;
}
