pci_restore_config_space_range(struct pci_dev *pdev,
					   int start, int end, int retry)
{
	int index;

	for (index = end; index >= start; index--)
		pci_restore_config_dword(pdev, 4 * index,
					 pdev->saved_config_space[index],
					 retry);
}
