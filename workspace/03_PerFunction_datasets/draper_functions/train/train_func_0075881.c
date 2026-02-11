r852_dma_test(struct r852_device *dev)
{
	dev->dma_usable = (r852_read_reg(dev, R852_DMA_CAP) &
		(R852_DMA1 | R852_DMA2)) == (R852_DMA1 | R852_DMA2);

	if (!dev->dma_usable)
		message("Non dma capable device detected, dma disabled");

	if (!r852_enable_dma) {
		message("disabling dma on user request");
		dev->dma_usable = 0;
	}
}
