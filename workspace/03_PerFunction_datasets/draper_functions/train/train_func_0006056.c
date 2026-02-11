pci_intx_mask_supported(struct pci_dev *dev)
{
	bool mask_supported = false;
	u16 orig, new;

	if (dev->broken_intx_masking)
		return false;

	pci_cfg_access_lock(dev);

	pci_read_config_word(dev, PCI_COMMAND, &orig);
	pci_write_config_word(dev, PCI_COMMAND,
			      orig ^ PCI_COMMAND_INTX_DISABLE);
	pci_read_config_word(dev, PCI_COMMAND, &new);


	if ((new ^ orig) & ~PCI_COMMAND_INTX_DISABLE) {
		dev_err(&dev->dev, "Command register changed from 0x%x to 0x%x: driver or hardware bug?\n",
			orig, new);
	} else if ((new ^ orig) & PCI_COMMAND_INTX_DISABLE) {
		mask_supported = true;
		pci_write_config_word(dev, PCI_COMMAND, orig);
	}

	pci_cfg_access_unlock(dev);
	return mask_supported;
}
