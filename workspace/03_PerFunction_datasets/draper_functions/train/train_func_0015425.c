do_cciss_msix_intr(int irq, void *dev_id)
{
	ctlr_info_t *h = dev_id;
	unsigned long flags;
	u32 raw_tag;

	spin_lock_irqsave(&h->lock, flags);
	raw_tag = get_next_completion(h);
	while (raw_tag != FIFO_EMPTY) {
		if (cciss_tag_contains_index(raw_tag))
			raw_tag = process_indexed_cmd(h, raw_tag);
		else
			raw_tag = process_nonindexed_cmd(h, raw_tag);
	}
	spin_unlock_irqrestore(&h->lock, flags);
	return IRQ_HANDLED;
}
