acard_ahci_configure_dma_masks(struct pci_dev *pdev, int using_dac)
{
	int rc;

	if (using_dac &&
	    !dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) {
		rc = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64));
		if (rc) {
			rc = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
			if (rc) {
				dev_err(&pdev->dev,
					   "64-bit DMA enable failed\n");
				return rc;
			}
		}
	} else {
		rc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		if (rc) {
			dev_err(&pdev->dev, "32-bit DMA enable failed\n");
			return rc;
		}
		rc = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
		if (rc) {
			dev_err(&pdev->dev,
				"32-bit consistent DMA enable failed\n");
			return rc;
		}
	}
	return 0;
}
