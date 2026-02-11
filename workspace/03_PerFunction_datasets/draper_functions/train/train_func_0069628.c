get_pci_alias_group(struct pci_dev *pdev,
					       unsigned long *devfns)
{
	struct pci_dev *tmp = NULL;
	struct iommu_group *group;

	if (test_and_set_bit(pdev->devfn & 0xff, devfns))
		return NULL;

	group = iommu_group_get(&pdev->dev);
	if (group)
		return group;

	for_each_pci_dev(tmp) {
		if (tmp == pdev || tmp->bus != pdev->bus)
			continue;


		if (((pdev->dev_flags & PCI_DEV_FLAGS_DMA_ALIAS_DEVFN) &&
		     pdev->dma_alias_devfn == tmp->devfn) ||
		    ((tmp->dev_flags & PCI_DEV_FLAGS_DMA_ALIAS_DEVFN) &&
		     tmp->dma_alias_devfn == pdev->devfn)) {

			group = get_pci_alias_group(tmp, devfns);
			if (group) {
				pci_dev_put(tmp);
				return group;
			}

			group = get_pci_function_alias_group(tmp, devfns);
			if (group) {
				pci_dev_put(tmp);
				return group;
			}
		}
	}

	return NULL;
}
