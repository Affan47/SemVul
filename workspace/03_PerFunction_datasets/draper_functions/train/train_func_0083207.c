cleanup_page_dma(struct drm_device *dev, struct i915_page_dma *p)
{
	if (WARN_ON(!p->page))
		return;

	dma_unmap_page(&dev->pdev->dev, p->daddr, 4096, PCI_DMA_BIDIRECTIONAL);
	__free_page(p->page);
	memset(p, 0, sizeof(*p));
}
