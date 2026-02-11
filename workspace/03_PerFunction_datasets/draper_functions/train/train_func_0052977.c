aer_error_resume(struct pci_dev *dev)
{
	int pos;
	u32 status, mask;
	u16 reg16;


	pcie_capability_read_word(dev, PCI_EXP_DEVSTA, &reg16);
	pcie_capability_write_word(dev, PCI_EXP_DEVSTA, reg16);


	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR);
	pci_read_config_dword(dev, pos + PCI_ERR_UNCOR_STATUS, &status);
	pci_read_config_dword(dev, pos + PCI_ERR_UNCOR_SEVER, &mask);
	if (dev->error_state == pci_channel_io_normal)
		status &= ~mask;
	else
		status &= mask;
	pci_write_config_dword(dev, pos + PCI_ERR_UNCOR_STATUS, status);
}
