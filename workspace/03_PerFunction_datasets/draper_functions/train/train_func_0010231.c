rtsx_pci_dma_map_sg(struct rtsx_pcr *pcr, struct scatterlist *sglist,
		int num_sg, bool read)
{
	enum dma_data_direction dir = read ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

	if (pcr->remove_pci)
		return -EINVAL;

	if ((sglist == NULL) || (num_sg <= 0))
		return -EINVAL;

	return dma_map_sg(&(pcr->pci->dev), sglist, num_sg, dir);
}
