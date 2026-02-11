free_dma_loaf(struct pci_dev *dev, struct dma_loaf *loaf_handle)
{
	if (loaf_handle->cpu_base != NULL)
		pci_free_consistent(dev, loaf_handle->length,
			loaf_handle->cpu_base, loaf_handle->dma_base);
}
