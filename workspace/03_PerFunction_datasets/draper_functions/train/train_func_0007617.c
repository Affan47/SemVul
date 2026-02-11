mempool_alloc(mempool_t *pool, gfp_t gfp_mask)
{
	void *element;
	unsigned long flags;
	wait_queue_t wait;
	gfp_t gfp_temp;

	VM_WARN_ON_ONCE(gfp_mask & __GFP_ZERO);
	might_sleep_if(gfp_mask & __GFP_DIRECT_RECLAIM);

	gfp_mask |= __GFP_NOMEMALLOC;
	gfp_mask |= __GFP_NORETRY;
	gfp_mask |= __GFP_NOWARN;

	gfp_temp = gfp_mask & ~(__GFP_DIRECT_RECLAIM|__GFP_IO);

repeat_alloc:

	element = pool->alloc(gfp_temp, pool->pool_data);
	if (likely(element != NULL))
		return element;

	spin_lock_irqsave(&pool->lock, flags);
	if (likely(pool->curr_nr)) {
		element = remove_element(pool);
		spin_unlock_irqrestore(&pool->lock, flags);

		smp_wmb();


		kmemleak_update_trace(element);
		return element;
	}


	if (gfp_temp != gfp_mask) {
		spin_unlock_irqrestore(&pool->lock, flags);
		gfp_temp = gfp_mask;
		goto repeat_alloc;
	}


	if (!(gfp_mask & __GFP_DIRECT_RECLAIM)) {
		spin_unlock_irqrestore(&pool->lock, flags);
		return NULL;
	}


	init_wait(&wait);
	prepare_to_wait(&pool->wait, &wait, TASK_UNINTERRUPTIBLE);

	spin_unlock_irqrestore(&pool->lock, flags);


	io_schedule_timeout(5*HZ);

	finish_wait(&pool->wait, &wait);
	goto repeat_alloc;
}
