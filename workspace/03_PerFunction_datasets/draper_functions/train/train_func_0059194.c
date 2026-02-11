mraid_mm_dealloc_kioc(mraid_mmadp_t *adp, uioc_t *kioc)
{
	mm_dmapool_t	*pool;
	unsigned long	flags;

	if (kioc->pool_index != -1) {
		pool = &adp->dma_pool_list[kioc->pool_index];


		spin_lock_irqsave(&pool->lock, flags);


		if (kioc->free_buf == 1)
			pci_pool_free(pool->handle, kioc->buf_vaddr,
							kioc->buf_paddr);
		else
			pool->in_use = 0;

		spin_unlock_irqrestore(&pool->lock, flags);
	}


	spin_lock_irqsave(&adp->kioc_pool_lock, flags);
	list_add(&kioc->list, &adp->kioc_pool);
	spin_unlock_irqrestore(&adp->kioc_pool_lock, flags);


	up(&adp->kioc_semaphore);

	return;
}
