lock_torture_writer(void *arg)
{
	struct lock_stress_stats *lwsp = arg;
	static DEFINE_TORTURE_RANDOM(rand);

	VERBOSE_TOROUT_STRING("lock_torture_writer task started");
	set_user_nice(current, MAX_NICE);

	do {
		if ((torture_random(&rand) & 0xfffff) == 0)
			schedule_timeout_uninterruptible(1);

		cxt.cur_ops->task_boost(&rand);
		cxt.cur_ops->writelock();
		if (WARN_ON_ONCE(lock_is_write_held))
			lwsp->n_lock_fail++;
		lock_is_write_held = 1;
		if (WARN_ON_ONCE(lock_is_read_held))
			lwsp->n_lock_fail++;

		lwsp->n_lock_acquired++;
		cxt.cur_ops->write_delay(&rand);
		lock_is_write_held = 0;
		cxt.cur_ops->writeunlock();

		stutter_wait("lock_torture_writer");
	} while (!torture_must_stop());

	cxt.cur_ops->task_boost(NULL);
	torture_kthread_stopping("lock_torture_writer");
	return 0;
}
