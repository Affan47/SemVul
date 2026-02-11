pci_create_resource_files(struct pci_dev *pdev)
{
	int i;
	int retval;


	for (i = 0; i < PCI_ROM_RESOURCE; i++) {


		if (!pci_resource_len(pdev, i))
			continue;

		retval = pci_create_attr(pdev, i, 0);

		if (!retval && pdev->resource[i].flags & IORESOURCE_PREFETCH)
			retval = pci_create_attr(pdev, i, 1);

		if (retval) {
			pci_remove_resource_files(pdev);
			return retval;
		}
	}
	return 0;
}
