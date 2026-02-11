mdc_issue_pending(struct dma_chan *chan)
{
	struct mdc_chan *mchan = to_mdc_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&mchan->vc.lock, flags);
	if (vchan_issue_pending(&mchan->vc) && !mchan->desc)
		mdc_issue_desc(mchan);
	spin_unlock_irqrestore(&mchan->vc.lock, flags);
}
