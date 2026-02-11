chan_irqt(int irq, void *dev)
{
	struct shdma_chan *schan = dev;
	const struct shdma_ops *ops =
		to_shdma_dev(schan->dma_chan.device)->ops;
	struct shdma_desc *sdesc;

	spin_lock_irq(&schan->chan_lock);
	list_for_each_entry(sdesc, &schan->ld_queue, node) {
		if (sdesc->mark == DESC_SUBMITTED &&
		    ops->desc_completed(schan, sdesc)) {
			dev_dbg(schan->dev, "done #%d@%p\n",
				sdesc->async_tx.cookie, &sdesc->async_tx);
			sdesc->mark = DESC_COMPLETED;
			break;
		}
	}

	shdma_chan_xfer_ld_queue(schan);
	spin_unlock_irq(&schan->chan_lock);

	shdma_chan_ld_cleanup(schan, false);

	return IRQ_HANDLED;
}
