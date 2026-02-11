rcar_dmac_of_xlate(struct of_phandle_args *dma_spec,
					   struct of_dma *ofdma)
{
	struct rcar_dmac_chan *rchan;
	struct dma_chan *chan;
	dma_cap_mask_t mask;

	if (dma_spec->args_count != 1)
		return NULL;


	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	chan = dma_request_channel(mask, rcar_dmac_chan_filter, dma_spec);
	if (!chan)
		return NULL;

	rchan = to_rcar_dmac_chan(chan);
	rchan->mid_rid = dma_spec->args[0];

	return chan;
}
