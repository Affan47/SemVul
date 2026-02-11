smq_lookup(struct dm_cache_policy *p, dm_oblock_t oblock, dm_cblock_t *cblock)
{
	int r;
	unsigned long flags;
	struct smq_policy *mq = to_smq_policy(p);
	struct entry *e;

	spin_lock_irqsave(&mq->lock, flags);
	e = h_lookup(&mq->table, oblock);
	if (e) {
		*cblock = infer_cblock(mq, e);
		r = 0;
	} else
		r = -ENOENT;
	spin_unlock_irqrestore(&mq->lock, flags);

	return r;
}
