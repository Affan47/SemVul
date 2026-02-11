__cleanup(struct ioatdma_chan *ioat_chan, dma_addr_t phys_complete)
{
	struct ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	struct ioat_ring_ent *desc;
	bool seen_current = false;
	int idx = ioat_chan->tail, i;
	u16 active;

	dev_dbg(to_dev(ioat_chan), "%s: head: %#x tail: %#x issued: %#x\n",
		__func__, ioat_chan->head, ioat_chan->tail, ioat_chan->issued);


	if (!phys_complete)
		return;

	active = ioat_ring_active(ioat_chan);
	for (i = 0; i < active && !seen_current; i++) {
		struct dma_async_tx_descriptor *tx;

		smp_read_barrier_depends();
		prefetch(ioat_get_ring_ent(ioat_chan, idx + i + 1));
		desc = ioat_get_ring_ent(ioat_chan, idx + i);
		dump_desc_dbg(ioat_chan, desc);


		if (ioat_dma->cap & IOAT_CAP_DWBES)
			desc_get_errstat(ioat_chan, desc);

		tx = &desc->txd;
		if (tx->cookie) {
			dma_cookie_complete(tx);
			dma_descriptor_unmap(tx);
			if (tx->callback) {
				tx->callback(tx->callback_param);
				tx->callback = NULL;
			}
		}

		if (tx->phys == phys_complete)
			seen_current = true;


		if (desc_has_ext(desc)) {
			BUG_ON(i + 1 >= active);
			i++;
		}


		if (desc->sed) {
			ioat_free_sed(ioat_dma, desc->sed);
			desc->sed = NULL;
		}
	}


	smp_mb();
	ioat_chan->tail = idx + i;

	BUG_ON(active && !seen_current);
	ioat_chan->last_completion = phys_complete;

	if (active - i == 0) {
		dev_dbg(to_dev(ioat_chan), "%s: cancel completion timeout\n",
			__func__);
		mod_timer(&ioat_chan->timer, jiffies + IDLE_TIMEOUT);
	}


	writew(min((5 * (active - i)), IOAT_INTRDELAY_MASK),
	       ioat_chan->ioat_dma->reg_base + IOAT_INTRDELAY_OFFSET);
}
