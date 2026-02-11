_find_list_dev(const struct device *dev,
					      struct device_opp *dev_opp)
{
	struct device_list_opp *list_dev;

	list_for_each_entry(list_dev, &dev_opp->dev_list, node)
		if (list_dev->dev == dev)
			return list_dev;

	return NULL;
}
