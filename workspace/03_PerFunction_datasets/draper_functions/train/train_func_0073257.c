xen_pcibk_reset_device(struct pci_dev *dev)
{
	u16 cmd;

	xen_pcibk_control_isr(dev, 1 );


	if (dev->hdr_type == PCI_HEADER_TYPE_NORMAL) {
#ifdef CONFIG_PCI_MSI


		if (dev->msix_enabled)
			pci_disable_msix(dev);
		if (dev->msi_enabled)
			pci_disable_msi(dev);
#endif
		if (pci_is_enabled(dev))
			pci_disable_device(dev);

		pci_write_config_word(dev, PCI_COMMAND, 0);

		dev->is_busmaster = 0;
	} else {
		pci_read_config_word(dev, PCI_COMMAND, &cmd);
		if (cmd & (PCI_COMMAND_INVALIDATE)) {
			cmd &= ~(PCI_COMMAND_INVALIDATE);
			pci_write_config_word(dev, PCI_COMMAND, cmd);

			dev->is_busmaster = 0;
		}
	}
}
