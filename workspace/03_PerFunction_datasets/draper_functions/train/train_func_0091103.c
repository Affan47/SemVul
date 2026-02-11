orc_release_scb(struct orc_host *host, struct orc_scb *scb)
{
	unsigned long flags;
	u8 index, i, channel;

	spin_lock_irqsave(&(host->allocation_lock), flags);
	channel = host->index;
	index = scb->scbidx;
	i = index / 32;
	index %= 32;
	host->allocation_map[channel][i] |= (1 << index);
	spin_unlock_irqrestore(&(host->allocation_lock), flags);
}
