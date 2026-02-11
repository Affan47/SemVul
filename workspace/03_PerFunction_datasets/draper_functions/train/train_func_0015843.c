snd_hammerfall_get_buffer(struct pci_dev *pci, struct snd_dma_buffer *dmab, size_t size)
{
	dmab->dev.type = SNDRV_DMA_TYPE_DEV;
	dmab->dev.dev = snd_dma_pci_data(pci);
	if (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, snd_dma_pci_data(pci),
				size, dmab) < 0)
		return -ENOMEM;
	return 0;
}
