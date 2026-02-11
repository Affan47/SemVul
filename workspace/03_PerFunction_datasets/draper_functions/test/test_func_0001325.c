gigaset_get_channel(struct bc_state *bcs)
{
	unsigned long flags;

	spin_lock_irqsave(&bcs->cs->lock, flags);
	if (bcs->use_count || !try_module_get(bcs->cs->driver->owner)) {
		gig_dbg(DEBUG_CHANNEL, "could not allocate channel %d",
			bcs->channel);
		spin_unlock_irqrestore(&bcs->cs->lock, flags);
		return -EBUSY;
	}
	++bcs->use_count;
	bcs->busy = 1;
	gig_dbg(DEBUG_CHANNEL, "allocated channel %d", bcs->channel);
	spin_unlock_irqrestore(&bcs->cs->lock, flags);
	return 0;
}
