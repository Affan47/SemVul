blogic_dealloc_ccb(struct blogic_ccb *ccb, int dma_unmap)
{
	struct blogic_adapter *adapter = ccb->adapter;

	if (ccb->command != NULL)
		scsi_dma_unmap(ccb->command);
	if (dma_unmap)
		pci_unmap_single(adapter->pci_device, ccb->sensedata,
			 ccb->sense_datalen, PCI_DMA_FROMDEVICE);

	ccb->command = NULL;
	ccb->status = BLOGIC_CCB_FREE;
	ccb->next = adapter->free_ccbs;
	adapter->free_ccbs = ccb;
}
