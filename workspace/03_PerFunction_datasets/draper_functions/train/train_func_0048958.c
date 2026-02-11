pci_read_bridge_bases(struct pci_bus *child)
{
	struct pci_dev *dev = child->self;
	struct resource *res;
	int i;

	if (pci_is_root_bus(child))
		return;

	dev_info(&dev->dev, "PCI bridge to %pR%s\n",
		 &child->busn_res,
		 dev->transparent ? " (subtractive decode)" : "");

	pci_bus_remove_resources(child);
	for (i = 0; i < PCI_BRIDGE_RESOURCE_NUM; i++)
		child->resource[i] = &dev->resource[PCI_BRIDGE_RESOURCES+i];

	pci_read_bridge_io(child);
	pci_read_bridge_mmio(child);
	pci_read_bridge_mmio_pref(child);

	if (dev->transparent) {
		pci_bus_for_each_resource(child->parent, res, i) {
			if (res && res->flags) {
				pci_bus_add_resource(child, res,
						     PCI_SUBTRACTIVE_DECODE);
				dev_printk(KERN_DEBUG, &dev->dev,
					   "  bridge window %pR (subtractive decode)\n",
					   res);
			}
		}
	}
}
