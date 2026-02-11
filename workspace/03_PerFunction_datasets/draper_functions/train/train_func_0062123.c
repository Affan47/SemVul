qib_free_lkey(struct qib_mregion *mr)
{
	unsigned long flags;
	u32 lkey = mr->lkey;
	u32 r;
	struct qib_ibdev *dev = to_idev(mr->pd->device);
	struct qib_lkey_table *rkt = &dev->lk_table;

	spin_lock_irqsave(&rkt->lock, flags);
	if (!mr->lkey_published)
		goto out;
	if (lkey == 0)
		RCU_INIT_POINTER(dev->dma_mr, NULL);
	else {
		r = lkey >> (32 - ib_qib_lkey_table_size);
		RCU_INIT_POINTER(rkt->table[r], NULL);
	}
	qib_put_mr(mr);
	mr->lkey_published = 0;
out:
	spin_unlock_irqrestore(&rkt->lock, flags);
}
