rcar_dmac_fill_hwdesc(struct rcar_dmac_chan *chan,
				 struct rcar_dmac_desc *desc)
{
	struct rcar_dmac_xfer_chunk *chunk;
	struct rcar_dmac_hw_desc *hwdesc;

	rcar_dmac_realloc_hwdesc(chan, desc, desc->nchunks * sizeof(*hwdesc));

	hwdesc = desc->hwdescs.mem;
	if (!hwdesc)
		return -ENOMEM;

	list_for_each_entry(chunk, &desc->chunks, node) {
		hwdesc->sar = chunk->src_addr;
		hwdesc->dar = chunk->dst_addr;
		hwdesc->tcr = chunk->size >> desc->xfer_shift;
		hwdesc++;
	}

	return 0;
}
