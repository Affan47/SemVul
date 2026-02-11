nbpf_chan_write(struct nbpf_channel *chan,
				   unsigned int offset, u32 data)
{
	iowrite32(data, chan->base + offset);
	dev_dbg(chan->dma_chan.device->dev, "%s(0x%p + 0x%x) = 0x%x\n",
		__func__, chan->base, offset, data);
}
