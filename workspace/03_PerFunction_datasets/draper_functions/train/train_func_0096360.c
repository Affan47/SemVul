hfi1_free_lkey(struct hfi1_mregion *mr)
{
	unsigned long flags;
	u32 lkey = mr->lkey;
	u32 r;
	struct hfi1_ibdev *dev = to_idev(mr->pd->device);
	struct hfi1_lkey_table *rkt = &dev->lk_table;
	int freed = 0;

	spin_lock_irqsave(&rkt->lock, flags);
	if (!mr->lkey_published)
		goto out;
	if (lkey == 0)
		RCU_INIT_POINTER(dev->dma_mr, NULL);
	else {
		r = lkey >> (32 - hfi1_lkey_table_size);
		RCU_INIT_POINTER(rkt->table[r], NULL);
	}
	mr->lkey_published = 0;
	freed++;
out:
	spin_unlock_irqrestore(&rkt->lock, flags);
	if (freed) {
		synchronize_rcu();
		hfi1_put_mr(mr);
	}
}
