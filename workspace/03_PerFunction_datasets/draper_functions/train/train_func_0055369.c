mdc_prep_dma_cyclic(
	struct dma_chan *chan, dma_addr_t buf_addr, size_t buf_len,
	size_t period_len, enum dma_transfer_direction dir,
	unsigned long flags)
{
	struct mdc_chan *mchan = to_mdc_chan(chan);
	struct mdc_dma *mdma = mchan->mdma;
	struct mdc_tx_desc *mdesc;
	struct mdc_hw_list_desc *curr, *prev = NULL;
	dma_addr_t curr_phys, prev_phys;

	if (!buf_len && !period_len)
		return NULL;

	if (!is_slave_direction(dir))
		return NULL;

	if (mdc_check_slave_width(mchan, dir) < 0)
		return NULL;

	mdesc = kzalloc(sizeof(*mdesc), GFP_NOWAIT);
	if (!mdesc)
		return NULL;
	mdesc->chan = mchan;
	mdesc->cyclic = true;
	mdesc->list_xfer_size = buf_len;
	mdesc->list_period_len = DIV_ROUND_UP(period_len,
					      mdma->max_xfer_size);

	while (buf_len > 0) {
		size_t remainder = min(period_len, buf_len);

		while (remainder > 0) {
			size_t xfer_size;

			curr = dma_pool_alloc(mdma->desc_pool, GFP_NOWAIT,
					      &curr_phys);
			if (!curr)
				goto free_desc;

			if (!prev) {
				mdesc->list_phys = curr_phys;
				mdesc->list = curr;
			} else {
				prev->node_addr = curr_phys;
				prev->next_desc = curr;
			}

			xfer_size = min_t(size_t, mdma->max_xfer_size,
					  remainder);

			if (dir == DMA_MEM_TO_DEV) {
				mdc_list_desc_config(mchan, curr, dir,
						     buf_addr,
						     mchan->config.dst_addr,
						     xfer_size);
			} else {
				mdc_list_desc_config(mchan, curr, dir,
						     mchan->config.src_addr,
						     buf_addr,
						     xfer_size);
			}

			prev = curr;
			prev_phys = curr_phys;

			mdesc->list_len++;
			buf_addr += xfer_size;
			buf_len -= xfer_size;
			remainder -= xfer_size;
		}
	}
	prev->node_addr = mdesc->list_phys;

	return vchan_tx_prep(&mchan->vc, &mdesc->vd, flags);

free_desc:
	mdc_desc_free(&mdesc->vd);

	return NULL;
}
