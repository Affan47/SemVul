pci_dev_run_wake(struct pci_dev *dev)
{
	struct pci_bus *bus = dev->bus;

	if (device_run_wake(&dev->dev))
		return true;

	if (!dev->pme_support)
		return false;


	if (!pci_pme_capable(dev, pci_target_state(dev)))
		return false;

	while (bus->parent) {
		struct pci_dev *bridge = bus->self;

		if (device_run_wake(&bridge->dev))
			return true;

		bus = bus->parent;
	}


	if (bus->bridge)
		return device_run_wake(bus->bridge);

	return false;
}
