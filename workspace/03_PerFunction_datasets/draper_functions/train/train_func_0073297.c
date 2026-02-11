fsl_edma_free_chan_resources(struct dma_chan *chan)
{
	struct fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
	fsl_edma_disable_request(fsl_chan);
	fsl_edma_chan_mux(fsl_chan, 0, false);
	fsl_chan->edesc = NULL;
	vchan_get_all_descriptors(&fsl_chan->vchan, &head);
	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);

	vchan_dma_desc_free_list(&fsl_chan->vchan, &head);
	dma_pool_destroy(fsl_chan->tcd_pool);
	fsl_chan->tcd_pool = NULL;
}
