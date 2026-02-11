detect_controller_lockup(struct ctlr_info *h)
{
	u64 now;
	u32 heartbeat;
	unsigned long flags;

	now = get_jiffies_64();

	if (time_after64(h->last_intr_timestamp +
				(h->heartbeat_sample_interval), now))
		return false;


	if (time_after64(h->last_heartbeat_timestamp +
				(h->heartbeat_sample_interval), now))
		return false;


	spin_lock_irqsave(&h->lock, flags);
	heartbeat = readl(&h->cfgtable->HeartBeat);
	spin_unlock_irqrestore(&h->lock, flags);
	if (h->last_heartbeat == heartbeat) {
		controller_lockup_detected(h);
		return true;
	}


	h->last_heartbeat = heartbeat;
	h->last_heartbeat_timestamp = now;
	return false;
}
