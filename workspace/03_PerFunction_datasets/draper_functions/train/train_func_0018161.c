copy_tick(struct mq_policy *mq)
{
	unsigned long flags, tick;

	spin_lock_irqsave(&mq->tick_lock, flags);
	tick = mq->tick_protected;
	if (tick != mq->tick) {
		queue_iterate_tick(&mq->pre_cache, update_pre_cache_hits, mq);
		queue_iterate_tick(&mq->cache_dirty, update_cache_hits, mq);
		queue_iterate_tick(&mq->cache_clean, update_cache_hits, mq);
		mq->tick = tick;
	}

	queue_tick(&mq->pre_cache);
	queue_tick(&mq->cache_dirty);
	queue_tick(&mq->cache_clean);
	queue_update_writeback_sentinels(&mq->cache_dirty);
	spin_unlock_irqrestore(&mq->tick_lock, flags);
}
