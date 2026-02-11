msi_setup_entry(struct pci_dev *dev, int nvec)
{
	u16 control;
	struct msi_desc *entry;


	entry = alloc_msi_entry(&dev->dev);
	if (!entry)
		return NULL;

	pci_read_config_word(dev, dev->msi_cap + PCI_MSI_FLAGS, &control);

	entry->msi_attrib.is_msix	= 0;
	entry->msi_attrib.is_64		= !!(control & PCI_MSI_FLAGS_64BIT);
	entry->msi_attrib.entry_nr	= 0;
	entry->msi_attrib.maskbit	= !!(control & PCI_MSI_FLAGS_MASKBIT);
	entry->msi_attrib.default_irq	= dev->irq;
	entry->msi_attrib.multi_cap	= (control & PCI_MSI_FLAGS_QMASK) >> 1;
	entry->msi_attrib.multiple	= ilog2(__roundup_pow_of_two(nvec));
	entry->nvec_used		= nvec;

	if (control & PCI_MSI_FLAGS_64BIT)
		entry->mask_pos = dev->msi_cap + PCI_MSI_MASK_64;
	else
		entry->mask_pos = dev->msi_cap + PCI_MSI_MASK_32;


	if (entry->msi_attrib.maskbit)
		pci_read_config_dword(dev, entry->mask_pos, &entry->masked);

	return entry;
}
