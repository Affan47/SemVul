pci_save_state(struct pci_dev *dev)
{
	int i;

	for (i = 0; i < 16; i++)
		pci_read_config_dword(dev, i * 4, &dev->saved_config_space[i]);
	dev->state_saved = true;

	i = pci_save_pcie_state(dev);
	if (i != 0)
		return i;

	i = pci_save_pcix_state(dev);
	if (i != 0)
		return i;

	return pci_save_vc_state(dev);
}
