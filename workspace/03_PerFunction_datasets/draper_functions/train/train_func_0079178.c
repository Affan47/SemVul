__remove_mapping(struct mq_policy *mq, dm_oblock_t oblock)
{
	struct entry *e;

	e = hash_lookup(mq, oblock);
	BUG_ON(!e || !in_cache(mq, e));

	del(mq, e);
	free_entry(&mq->cache_pool, e);
}
