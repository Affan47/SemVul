issue(struct thin_c *tc, struct bio *bio)
{
	struct pool *pool = tc->pool;
	unsigned long flags;

	if (!bio_triggers_commit(tc, bio)) {
		generic_make_request(bio);
		return;
	}


	if (dm_thin_aborted_changes(tc->td)) {
		bio_io_error(bio);
		return;
	}


	spin_lock_irqsave(&pool->lock, flags);
	bio_list_add(&pool->deferred_flush_bios, bio);
	spin_unlock_irqrestore(&pool->lock, flags);
}
