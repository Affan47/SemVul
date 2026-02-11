nbpf_free_chan_resources(struct dma_chan *dchan)
{
	struct nbpf_channel *chan = nbpf_to_chan(dchan);
	struct nbpf_desc_page *dpage, *tmp;

	dev_dbg(dchan->device->dev, "Entry %s()\n", __func__);

	nbpf_chan_halt(chan);
	nbpf_chan_idle(chan);

	nbpf_chan_prepare_default(chan);

	list_for_each_entry_safe(dpage, tmp, &chan->desc_page, node) {
		struct nbpf_link_desc *ldesc;
		int i;
		list_del(&dpage->node);
		for (i = 0, ldesc = dpage->ldesc;
		     i < ARRAY_SIZE(dpage->ldesc);
		     i++, ldesc++)
			dma_unmap_single(dchan->device->dev, ldesc->hwdesc_dma_addr,
					 sizeof(*ldesc->hwdesc), DMA_TO_DEVICE);
		free_page((unsigned long)dpage);
	}
}
