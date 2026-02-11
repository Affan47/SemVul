rcar_dmac_chan_get_residue(struct rcar_dmac_chan *chan,
					       dma_cookie_t cookie)
{
	struct rcar_dmac_desc *desc = chan->desc.running;
	struct rcar_dmac_xfer_chunk *running = NULL;
	struct rcar_dmac_xfer_chunk *chunk;
	unsigned int residue = 0;
	unsigned int dptr = 0;

	if (!desc)
		return 0;


	if (cookie != desc->async_tx.cookie)
		return desc->size;


	if (desc->hwdescs.use) {
		dptr = (rcar_dmac_chan_read(chan, RCAR_DMACHCRB) &
			RCAR_DMACHCRB_DPTR_MASK) >> RCAR_DMACHCRB_DPTR_SHIFT;
		WARN_ON(dptr >= desc->nchunks);
	} else {
		running = desc->running;
	}


	list_for_each_entry_reverse(chunk, &desc->chunks, node) {
		if (chunk == running || ++dptr == desc->nchunks)
			break;

		residue += chunk->size;
	}


	residue += rcar_dmac_chan_read(chan, RCAR_DMATCR) << desc->xfer_shift;

	return residue;
}
