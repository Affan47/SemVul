nct6775_in_is_visible(struct kobject *kobj,
				     struct attribute *attr, int index)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	struct nct6775_data *data = dev_get_drvdata(dev);
	int in = index / 5;

	if (!(data->have_in & (1 << in)))
		return 0;

	return attr->mode;
}
