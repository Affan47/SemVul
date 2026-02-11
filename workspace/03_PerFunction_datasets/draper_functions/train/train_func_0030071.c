insert_in_cache(struct smq_policy *mq, dm_oblock_t oblock,
			    struct policy_locker *locker,
			    struct policy_result *result, enum promote_result pr)
{
	int r;
	struct entry *e;

	if (allocator_empty(&mq->cache_alloc)) {
		result->op = POLICY_REPLACE;
		r = demote_cblock(mq, locker, &result->old_oblock);
		if (r) {
			result->op = POLICY_MISS;
			return;
		}

	} else
		result->op = POLICY_NEW;

	e = alloc_entry(&mq->cache_alloc);
	BUG_ON(!e);
	e->oblock = oblock;

	if (pr == PROMOTE_TEMPORARY)
		push(mq, e);
	else
		push_new(mq, e);

	result->cblock = infer_cblock(mq, e);
}
