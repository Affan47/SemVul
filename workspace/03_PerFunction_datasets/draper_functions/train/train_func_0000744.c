ioc_release_fn(struct work_struct *work)
{
	struct io_context *ioc = container_of(work, struct io_context,
					      release_work);
	unsigned long flags;


	spin_lock_irqsave_nested(&ioc->lock, flags, 1);

	while (!hlist_empty(&ioc->icq_list)) {
		struct io_cq *icq = hlist_entry(ioc->icq_list.first,
						struct io_cq, ioc_node);
		struct request_queue *q = icq->q;

		if (spin_trylock(q->queue_lock)) {
			ioc_destroy_icq(icq);
			spin_unlock(q->queue_lock);
		} else {
			spin_unlock_irqrestore(&ioc->lock, flags);
			cpu_relax();
			spin_lock_irqsave_nested(&ioc->lock, flags, 1);
		}
	}

	spin_unlock_irqrestore(&ioc->lock, flags);

	kmem_cache_free(iocontext_cachep, ioc);
}
