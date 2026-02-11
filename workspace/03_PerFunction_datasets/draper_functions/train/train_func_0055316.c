pci_restore_config_space(struct pci_dev *pdev)
{
	if (pdev->hdr_type == PCI_HEADER_TYPE_NORMAL) {
		pci_restore_config_space_range(pdev, 10, 15, 0);

		pci_restore_config_space_range(pdev, 4, 9, 10);
		pci_restore_config_space_range(pdev, 0, 3, 0);
	} else {
		pci_restore_config_space_range(pdev, 0, 15, 0);
	}
}
