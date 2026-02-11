ib_destroy_fmr_pool(struct ib_fmr_pool *pool)
{
	struct ib_pool_fmr *fmr;
	struct ib_pool_fmr *tmp;
	LIST_HEAD(fmr_list);
	int                 i;

	kthread_stop(pool->thread);
	ib_fmr_batch_release(pool);

	i = 0;
	list_for_each_entry_safe(fmr, tmp, &pool->free_list, list) {
		if (fmr->remap_count) {
			INIT_LIST_HEAD(&fmr_list);
			list_add_tail(&fmr->fmr->list, &fmr_list);
			ib_unmap_fmr(&fmr_list);
		}
		ib_dealloc_fmr(fmr->fmr);
		list_del(&fmr->list);
		kfree(fmr);
		++i;
	}

	if (i < pool->pool_size)
		printk(KERN_WARNING PFX "pool still has %d regions registered\n",
		       pool->pool_size - i);

	kfree(pool->cache_bucket);
	kfree(pool);
}
