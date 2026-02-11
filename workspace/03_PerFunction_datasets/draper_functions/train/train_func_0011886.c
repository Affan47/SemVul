ivtv_udma_free(struct ivtv *itv)
{
	int i;


	if (itv->udma.SG_handle) {
		pci_unmap_single(itv->pdev, itv->udma.SG_handle,
			 sizeof(itv->udma.SGarray), PCI_DMA_TODEVICE);
	}


	if (itv->udma.SG_length) {
		pci_unmap_sg(itv->pdev, itv->udma.SGlist, itv->udma.page_count, PCI_DMA_TODEVICE);
	}

	for (i = 0; i < IVTV_DMA_SG_OSD_ENT; i++) {
		if (itv->udma.bouncemap[i])
			__free_page(itv->udma.bouncemap[i]);
	}
}
