dma_get_slave_caps(struct dma_chan *chan, struct dma_slave_caps *caps)
{
	struct dma_device *device;

	if (!chan || !caps)
		return -EINVAL;

	device = chan->device;


	if (!test_bit(DMA_SLAVE, device->cap_mask.bits))
		return -ENXIO;


	if (!device->directions)
		return -ENXIO;

	caps->src_addr_widths = device->src_addr_widths;
	caps->dst_addr_widths = device->dst_addr_widths;
	caps->directions = device->directions;
	caps->residue_granularity = device->residue_granularity;


	caps->cmd_pause = !!(device->device_pause && device->device_resume);
	caps->cmd_terminate = !!device->device_terminate_all;

	return 0;
}
