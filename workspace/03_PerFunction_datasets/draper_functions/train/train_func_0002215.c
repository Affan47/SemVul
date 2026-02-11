component_bind_all(struct device *master_dev, void *data)
{
	struct master *master;
	struct component *c;
	int ret = 0;

	WARN_ON(!mutex_is_locked(&component_mutex));

	master = __master_find(master_dev, NULL);
	if (!master)
		return -EINVAL;

	list_for_each_entry(c, &master->components, master_node) {
		ret = component_bind(c, master, data);
		if (ret)
			break;
	}

	if (ret != 0) {
		list_for_each_entry_continue_reverse(c, &master->components,
						     master_node)
			component_unbind(c, master, data);
	}

	return ret;
}
