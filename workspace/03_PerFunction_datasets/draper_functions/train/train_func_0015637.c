fsl_edma_tx_status(struct dma_chan *chan,
		dma_cookie_t cookie, struct dma_tx_state *txstate)
{
	struct fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	struct virt_dma_desc *vdesc;
	enum dma_status status;
	unsigned long flags;

	status = dma_cookie_status(chan, cookie, txstate);
	if (status == DMA_COMPLETE)
		return status;

	if (!txstate)
		return fsl_chan->status;

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
	vdesc = vchan_find_desc(&fsl_chan->vchan, cookie);
	if (fsl_chan->edesc && cookie == fsl_chan->edesc->vdesc.tx.cookie)
		txstate->residue = fsl_edma_desc_residue(fsl_chan, vdesc, true);
	else if (vdesc)
		txstate->residue = fsl_edma_desc_residue(fsl_chan, vdesc, false);
	else
		txstate->residue = 0;

	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);

	return fsl_chan->status;
}
