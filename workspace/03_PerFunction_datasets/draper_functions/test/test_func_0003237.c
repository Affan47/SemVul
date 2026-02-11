mq_map(struct dm_cache_policy *p, dm_oblock_t oblock,
		  bool can_block, bool can_migrate, bool discarded_oblock,
		  struct bio *bio, struct policy_locker *locker,
		  struct policy_result *result)
{
	int r;
	struct mq_policy *mq = to_mq_policy(p);

	result->op = POLICY_MISS;

	if (can_block)
		mutex_lock(&mq->lock);
	else if (!mutex_trylock(&mq->lock))
		return -EWOULDBLOCK;

	copy_tick(mq);

	iot_examine_bio(&mq->tracker, bio);
	r = map(mq, oblock, can_migrate, discarded_oblock,
		bio_data_dir(bio), locker, result);

	mutex_unlock(&mq->lock);

	return r;
}
