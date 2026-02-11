__xen_pcibk_get_pci_dev(struct xen_pcibk_device *pdev,
					       unsigned int domain,
					       unsigned int bus,
					       unsigned int devfn)
{
	struct passthrough_dev_data *dev_data = pdev->pci_dev_data;
	struct pci_dev_entry *dev_entry;
	struct pci_dev *dev = NULL;

	mutex_lock(&dev_data->lock);

	list_for_each_entry(dev_entry, &dev_data->dev_list, list) {
		if (domain == (unsigned int)pci_domain_nr(dev_entry->dev->bus)
		    && bus == (unsigned int)dev_entry->dev->bus->number
		    && devfn == dev_entry->dev->devfn) {
			dev = dev_entry->dev;
			break;
		}
	}

	mutex_unlock(&dev_data->lock);

	return dev;
}
