mdc_tx_status(struct dma_chan *chan,
	dma_cookie_t cookie, struct dma_tx_state *txstate)
{
	struct mdc_chan *mchan = to_mdc_chan(chan);
	struct mdc_tx_desc *mdesc;
	struct virt_dma_desc *vd;
	unsigned long flags;
	size_t bytes = 0;
	int ret;

	ret = dma_cookie_status(chan, cookie, txstate);
	if (ret == DMA_COMPLETE)
		return ret;

	if (!txstate)
		return ret;

	spin_lock_irqsave(&mchan->vc.lock, flags);
	vd = vchan_find_desc(&mchan->vc, cookie);
	if (vd) {
		mdesc = to_mdc_desc(&vd->tx);
		bytes = mdesc->list_xfer_size;
	} else if (mchan->desc && mchan->desc->vd.tx.cookie == cookie) {
		struct mdc_hw_list_desc *ldesc;
		u32 val1, val2, done, processed, residue;
		int i, cmds;

		mdesc = mchan->desc;


		do {
			val1 = mdc_chan_readl(mchan, MDC_CMDS_PROCESSED) &
				~MDC_CMDS_PROCESSED_INT_ACTIVE;
			residue = mdc_chan_readl(mchan,
						 MDC_ACTIVE_TRANSFER_SIZE);
			val2 = mdc_chan_readl(mchan, MDC_CMDS_PROCESSED) &
				~MDC_CMDS_PROCESSED_INT_ACTIVE;
		} while (val1 != val2);

		done = (val1 >> MDC_CMDS_PROCESSED_CMDS_DONE_SHIFT) &
			MDC_CMDS_PROCESSED_CMDS_DONE_MASK;
		processed = (val1 >> MDC_CMDS_PROCESSED_CMDS_PROCESSED_SHIFT) &
			MDC_CMDS_PROCESSED_CMDS_PROCESSED_MASK;
		cmds = (done - processed) %
			(MDC_CMDS_PROCESSED_CMDS_DONE_MASK + 1);


		if (!mdesc->cmd_loaded)
			cmds--;
		else
			cmds += mdesc->list_cmds_done;

		bytes = mdesc->list_xfer_size;
		ldesc = mdesc->list;
		for (i = 0; i < cmds; i++) {
			bytes -= ldesc->xfer_size + 1;
			ldesc = ldesc->next_desc;
		}
		if (ldesc) {
			if (residue != MDC_TRANSFER_SIZE_MASK)
				bytes -= ldesc->xfer_size - residue;
			else
				bytes -= ldesc->xfer_size + 1;
		}
	}
	spin_unlock_irqrestore(&mchan->vc.lock, flags);

	dma_set_residue(txstate, bytes);

	return ret;
}
