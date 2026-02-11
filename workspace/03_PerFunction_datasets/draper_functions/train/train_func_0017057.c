subsys_register(struct bus_type *subsys,
			   const struct attribute_group **groups,
			   struct kobject *parent_of_root)
{
	struct device *dev;
	int err;

	err = bus_register(subsys);
	if (err < 0)
		return err;

	dev = kzalloc(sizeof(struct device), GFP_KERNEL);
	if (!dev) {
		err = -ENOMEM;
		goto err_dev;
	}

	err = dev_set_name(dev, "%s", subsys->name);
	if (err < 0)
		goto err_name;

	dev->kobj.parent = parent_of_root;
	dev->groups = groups;
	dev->release = system_root_device_release;

	err = device_register(dev);
	if (err < 0)
		goto err_dev_reg;

	subsys->dev_root = dev;
	return 0;

err_dev_reg:
	put_device(dev);
	dev = NULL;
err_name:
	kfree(dev);
err_dev:
	bus_unregister(subsys);
	return err;
}
