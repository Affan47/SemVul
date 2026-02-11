store_als_attr(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct lm3533_als_attribute *als_attr = to_lm3533_als_attr(attr);
	u8 val;
	int ret;

	if (kstrtou8(buf, 0, &val))
		return -EINVAL;

	switch (als_attr->type) {
	case LM3533_ATTR_TYPE_TARGET:
		ret = lm3533_als_set_target(indio_dev, als_attr->val1,
							als_attr->val2, val);
		break;
	case LM3533_ATTR_TYPE_THRESH_FALLING:
		ret = lm3533_als_set_threshold(indio_dev, als_attr->val1,
								false, val);
		break;
	case LM3533_ATTR_TYPE_THRESH_RAISING:
		ret = lm3533_als_set_threshold(indio_dev, als_attr->val1,
								true, val);
		break;
	default:
		ret = -ENXIO;
	}

	if (ret)
		return ret;

	return len;
}
