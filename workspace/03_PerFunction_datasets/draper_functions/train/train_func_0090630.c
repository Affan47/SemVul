insert_in_cache(struct mq_policy *mq, dm_oblock_t oblock,
			    struct policy_locker *locker,
			    struct policy_result *result)
{
	int r;
	struct entry *e;

	if (epool_empty(&mq->cache_pool)) {
		result->op = POLICY_REPLACE;
		r = demote_cblock(mq, locker, &result->old_oblock);
		if (unlikely(r)) {
			result->op = POLICY_MISS;
			insert_in_pre_cache(mq, oblock);
			return;
		}


		e = alloc_entry(&mq->cache_pool);
		BUG_ON(!e);

	} else {
		e = alloc_entry(&mq->cache_pool);
		result->op = POLICY_NEW;
	}

	e->oblock = oblock;
	e->dirty = false;
	e->hit_count = 1;
	push(mq, e);

	result->cblock = infer_cblock(&mq->cache_pool, e);
}
