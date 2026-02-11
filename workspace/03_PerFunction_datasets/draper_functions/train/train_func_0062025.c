nbpf_desc_page_alloc(struct nbpf_channel *chan)
{
	struct dma_chan *dchan = &chan->dma_chan;
	struct nbpf_desc_page *dpage = (void *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	struct nbpf_link_desc *ldesc;
	struct nbpf_link_reg *hwdesc;
	struct nbpf_desc *desc;
	LIST_HEAD(head);
	LIST_HEAD(lhead);
	int i;
	struct device *dev = dchan->device->dev;

	if (!dpage)
		return -ENOMEM;

	dev_dbg(dev, "%s(): alloc %lu descriptors, %lu segments, total alloc %zu\n",
		__func__, NBPF_DESCS_PER_PAGE, NBPF_SEGMENTS_PER_PAGE, sizeof(*dpage));

	for (i = 0, ldesc = dpage->ldesc, hwdesc = dpage->hwdesc;
	     i < ARRAY_SIZE(dpage->ldesc);
	     i++, ldesc++, hwdesc++) {
		ldesc->hwdesc = hwdesc;
		list_add_tail(&ldesc->node, &lhead);
		ldesc->hwdesc_dma_addr = dma_map_single(dchan->device->dev,
					hwdesc, sizeof(*hwdesc), DMA_TO_DEVICE);

		dev_dbg(dev, "%s(): mapped 0x%p to %pad\n", __func__,
			hwdesc, &ldesc->hwdesc_dma_addr);
	}

	for (i = 0, desc = dpage->desc;
	     i < ARRAY_SIZE(dpage->desc);
	     i++, desc++) {
		dma_async_tx_descriptor_init(&desc->async_tx, dchan);
		desc->async_tx.tx_submit = nbpf_tx_submit;
		desc->chan = chan;
		INIT_LIST_HEAD(&desc->sg);
		list_add_tail(&desc->node, &head);
	}


	spin_lock_irq(&chan->lock);
	list_splice_tail(&lhead, &chan->free_links);
	list_splice_tail(&head, &chan->free);
	list_add(&dpage->node, &chan->desc_page);
	spin_unlock_irq(&chan->lock);

	return ARRAY_SIZE(dpage->desc);
}
