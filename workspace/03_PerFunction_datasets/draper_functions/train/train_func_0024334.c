fpga_mgr_register(struct device *dev, const char *name,
		      const struct fpga_manager_ops *mops,
		      void *priv)
{
	struct fpga_manager *mgr;
	int id, ret;

	if (!mops || !mops->write_init || !mops->write ||
	    !mops->write_complete || !mops->state) {
		dev_err(dev, "Attempt to register without fpga_manager_ops\n");
		return -EINVAL;
	}

	if (!name || !strlen(name)) {
		dev_err(dev, "Attempt to register with no name!\n");
		return -EINVAL;
	}

	mgr = kzalloc(sizeof(*mgr), GFP_KERNEL);
	if (!mgr)
		return -ENOMEM;

	id = ida_simple_get(&fpga_mgr_ida, 0, 0, GFP_KERNEL);
	if (id < 0) {
		ret = id;
		goto error_kfree;
	}

	mutex_init(&mgr->ref_mutex);

	mgr->name = name;
	mgr->mops = mops;
	mgr->priv = priv;


	mgr->state = mgr->mops->state(mgr);

	device_initialize(&mgr->dev);
	mgr->dev.class = fpga_mgr_class;
	mgr->dev.parent = dev;
	mgr->dev.of_node = dev->of_node;
	mgr->dev.id = id;
	dev_set_drvdata(dev, mgr);

	ret = dev_set_name(&mgr->dev, "fpga%d", id);
	if (ret)
		goto error_device;

	ret = device_add(&mgr->dev);
	if (ret)
		goto error_device;

	dev_info(&mgr->dev, "%s registered\n", mgr->name);

	return 0;

error_device:
	ida_simple_remove(&fpga_mgr_ida, id);
error_kfree:
	kfree(mgr);

	return ret;
}
