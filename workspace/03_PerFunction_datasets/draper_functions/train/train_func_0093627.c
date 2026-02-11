ioat_irq_reinit(struct ioatdma_device *ioat_dma)
{
	struct pci_dev *pdev = ioat_dma->pdev;
	int irq = pdev->irq, i;

	if (!is_bwd_ioat(pdev))
		return 0;

	switch (ioat_dma->irq_mode) {
	case IOAT_MSIX:
		for (i = 0; i < ioat_dma->dma_dev.chancnt; i++) {
			struct msix_entry *msix = &ioat_dma->msix_entries[i];
			struct ioatdma_chan *ioat_chan;

			ioat_chan = ioat_chan_by_index(ioat_dma, i);
			devm_free_irq(&pdev->dev, msix->vector, ioat_chan);
		}

		pci_disable_msix(pdev);
		break;
	case IOAT_MSI:
		pci_disable_msi(pdev);

	case IOAT_INTX:
		devm_free_irq(&pdev->dev, irq, ioat_dma);
		break;
	default:
		return 0;
	}
	ioat_dma->irq_mode = IOAT_NOIRQ;

	return ioat_dma_setup_interrupts(ioat_dma);
}
