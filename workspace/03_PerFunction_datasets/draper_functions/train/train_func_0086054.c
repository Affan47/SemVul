xen_swiotlb_set_dma_mask(struct device *dev, u64 dma_mask)
{
	if (!dev->dma_mask || !xen_swiotlb_dma_supported(dev, dma_mask))
		return -EIO;

	*dev->dma_mask = dma_mask;

	return 0;
}
