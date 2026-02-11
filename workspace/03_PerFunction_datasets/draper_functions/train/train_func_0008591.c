it821x_init_one(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct it821x_dev *itdevs;
	int rc;

	itdevs = kzalloc(2 * sizeof(*itdevs), GFP_KERNEL);
	if (itdevs == NULL) {
		printk(KERN_ERR DRV_NAME " %s: out of memory\n", pci_name(dev));
		return -ENOMEM;
	}

	itdevs->quirks = id->driver_data;

	rc = ide_pci_init_one(dev, &it821x_chipset, itdevs);
	if (rc)
		kfree(itdevs);

	return rc;
}
