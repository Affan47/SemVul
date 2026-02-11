mark_held_locks(struct task_struct *curr, enum mark_type mark)
{
	enum lock_usage_bit usage_bit;
	struct held_lock *hlock;
	int i;

	for (i = 0; i < curr->lockdep_depth; i++) {
		hlock = curr->held_locks + i;

		usage_bit = 2 + (mark << 2);
		if (hlock->read)
			usage_bit += 1;

		BUG_ON(usage_bit >= LOCK_USAGE_STATES);

		if (!hlock->check)
			continue;

		if (!mark_lock(curr, hlock, usage_bit))
			return 0;
	}

	return 1;
}
