sh_mobile_i2c_dma_unmap(struct sh_mobile_i2c_data *pd)
{
	struct dma_chan *chan = pd->dma_direction == DMA_FROM_DEVICE
				? pd->dma_rx : pd->dma_tx;

	dma_unmap_single(chan->device->dev, sg_dma_address(&pd->sg),
			 pd->msg->len, pd->dma_direction);

	pd->dma_direction = DMA_NONE;
}
