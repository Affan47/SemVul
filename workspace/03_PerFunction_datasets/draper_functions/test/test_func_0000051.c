edd_attr_show(struct kobject * kobj, struct attribute *attr, char *buf)
{
	struct edd_device *dev = to_edd_device(kobj);
	struct edd_attribute *edd_attr = to_edd_attr(attr);
	ssize_t ret = -EIO;

	if (edd_attr->show)
		ret = edd_attr->show(dev, buf);
	return ret;
}
