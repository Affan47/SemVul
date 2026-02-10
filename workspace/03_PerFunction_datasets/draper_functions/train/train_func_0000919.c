intel_dc21285_init(struct pci_dev *dev, struct map_pci_info *map)
{
	unsigned long base, len;

	base = pci_resource_start(dev, PCI_ROM_RESOURCE);
	len  = pci_resource_len(dev, PCI_ROM_RESOURCE);

	if (!len || !base) {


		base = pci_resource_start(dev, 2);
		len  = pci_resource_len(dev, 2);


	} else {


		pci_enable_rom(dev);
		printk("%s: enabling expansion ROM\n", pci_name(dev));
	}

	if (!len || !base)
		return -ENXIO;

	map->map.bankwidth = 4;
	map->map.read = mtd_pci_read32,
	map->map.write = mtd_pci_write32,
	map->map.size     = len;
	map->base         = ioremap_nocache(base, len);

	if (!map->base)
		return -ENOMEM;

	return 0;
}
