pci_read_bases(struct pci_dev *dev, unsigned int howmany, int rom)
{
	unsigned int pos, reg;

	if (dev->non_compliant_bars)
		return;

	for (pos = 0; pos < howmany; pos++) {
		struct resource *res = &dev->resource[pos];
		reg = PCI_BASE_ADDRESS_0 + (pos << 2);
		pos += __pci_read_base(dev, pci_bar_unknown, res, reg);
	}

	if (rom) {
		struct resource *res = &dev->resource[PCI_ROM_RESOURCE];
		dev->rom_base_reg = rom;
		res->flags = IORESOURCE_MEM | IORESOURCE_PREFETCH |
				IORESOURCE_READONLY | IORESOURCE_SIZEALIGN;
		__pci_read_base(dev, pci_bar_mem32, res, rom);
	}
}
