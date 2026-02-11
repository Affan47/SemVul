wb_writeback_work(struct dm_cache_policy *pe,
			     dm_oblock_t *oblock,
			     dm_cblock_t *cblock,
			     bool critical_only)
{
	int r = -ENOENT;
	struct policy *p = to_policy(pe);
	struct wb_cache_entry *e;
	unsigned long flags;

	spin_lock_irqsave(&p->lock, flags);

	e = get_next_dirty_entry(p);
	if (e) {
		*oblock = e->oblock;
		*cblock = e->cblock;
		r = 0;
	}

	spin_unlock_irqrestore(&p->lock, flags);

	return r;
}
