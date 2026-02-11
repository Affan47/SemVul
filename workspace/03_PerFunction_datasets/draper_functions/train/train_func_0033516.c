iommu_device_create(struct device *parent, void *drvdata,
				   const struct attribute_group **groups,
				   const char *fmt, ...)
{
	struct device *dev;
	va_list vargs;
	int ret;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return ERR_PTR(-ENOMEM);

	device_initialize(dev);

	dev->class = &iommu_class;
	dev->parent = parent;
	dev->groups = groups;
	dev_set_drvdata(dev, drvdata);

	va_start(vargs, fmt);
	ret = kobject_set_name_vargs(&dev->kobj, fmt, vargs);
	va_end(vargs);
	if (ret)
		goto error;

	ret = device_add(dev);
	if (ret)
		goto error;

	return dev;

error:
	put_device(dev);
	return ERR_PTR(ret);
}
