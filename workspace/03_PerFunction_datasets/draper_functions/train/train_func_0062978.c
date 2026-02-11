pre_cache_entry_found(struct mq_policy *mq, struct entry *e,
				 bool can_migrate, bool discarded_oblock,
				 int data_dir, struct policy_locker *locker,
				 struct policy_result *result)
{
	int r = 0;

	if (!should_promote(mq, e, discarded_oblock, data_dir)) {
		requeue(mq, e);
		result->op = POLICY_MISS;

	} else if (!can_migrate)
		r = -EWOULDBLOCK;

	else {
		requeue(mq, e);
		r = pre_cache_to_cache(mq, e, locker, result);
	}

	return r;
}
