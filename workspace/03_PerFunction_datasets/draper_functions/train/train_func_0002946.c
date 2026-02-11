isci_pci_init(struct pci_dev *pdev)
{
	int err, bar_num, bar_mask = 0;
	void __iomem * const *iomap;

	err = pcim_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev,
			"failed enable PCI device %s!\n",
			pci_name(pdev));
		return err;
	}

	for (bar_num = 0; bar_num < SCI_PCI_BAR_COUNT; bar_num++)
		bar_mask |= 1 << (bar_num * 2);

	err = pcim_iomap_regions(pdev, bar_mask, DRV_NAME);
	if (err)
		return err;

	iomap = pcim_iomap_table(pdev);
	if (!iomap)
		return -ENOMEM;

	pci_set_master(pdev);

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	if (err) {
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (err)
			return err;
	}

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	if (err) {
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		if (err)
			return err;
	}

	return 0;
}
