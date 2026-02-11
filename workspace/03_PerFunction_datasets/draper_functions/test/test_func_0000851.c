rtsx_pci_acquire_irq(struct rtsx_pcr *pcr)
{
	dev_info(&(pcr->pci->dev), "%s: pcr->msi_en = %d, pci->irq = %d\n",
			__func__, pcr->msi_en, pcr->pci->irq);

	if (request_irq(pcr->pci->irq, rtsx_pci_isr,
			pcr->msi_en ? 0 : IRQF_SHARED,
			DRV_NAME_RTSX_PCI, pcr)) {
		dev_err(&(pcr->pci->dev),
			"rtsx_sdmmc: unable to grab IRQ %d, disabling device\n",
			pcr->pci->irq);
		return -1;
	}

	pcr->irq = pcr->pci->irq;
	pci_intx(pcr->pci, !pcr->msi_en);

	return 0;
}
