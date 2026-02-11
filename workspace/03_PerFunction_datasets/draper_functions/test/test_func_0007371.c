fscache_wait_for_deferred_lookup(struct fscache_cookie *cookie)
{
	unsigned long jif;

	_enter("");

	if (!test_bit(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags)) {
		_leave(" = 0 [imm]");
		return 0;
	}

	fscache_stat(&fscache_n_retrievals_wait);

	jif = jiffies;
	if (wait_on_bit(&cookie->flags, FSCACHE_COOKIE_LOOKING_UP,
			TASK_INTERRUPTIBLE) != 0) {
		fscache_stat(&fscache_n_retrievals_intr);
		_leave(" = -ERESTARTSYS");
		return -ERESTARTSYS;
	}

	ASSERT(!test_bit(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags));

	smp_rmb();
	fscache_hist(fscache_retrieval_delay_histogram, jif);
	_leave(" = 0 [dly]");
	return 0;
}
