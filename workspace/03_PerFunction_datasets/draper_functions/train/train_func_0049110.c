bus_remove_device(struct device *dev)
{
	struct bus_type *bus = dev->bus;
	struct subsys_interface *sif;

	if (!bus)
		return;

	mutex_lock(&bus->p->mutex);
	list_for_each_entry(sif, &bus->p->interfaces, node)
		if (sif->remove_dev)
			sif->remove_dev(dev, sif);
	mutex_unlock(&bus->p->mutex);

	sysfs_remove_link(&dev->kobj, "subsystem");
	sysfs_remove_link(&dev->bus->p->devices_kset->kobj,
			  dev_name(dev));
	device_remove_attrs(dev->bus, dev);
	device_remove_groups(dev, dev->bus->dev_groups);
	if (klist_node_attached(&dev->p->knode_bus))
		klist_del(&dev->p->knode_bus);

	pr_debug("bus: '%s': remove device %s\n",
		 dev->bus->name, dev_name(dev));
	device_release_driver(dev);
	bus_put(dev->bus);
}
