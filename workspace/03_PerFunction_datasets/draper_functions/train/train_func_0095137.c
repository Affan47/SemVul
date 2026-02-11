thread_suspend_self(volatile struct thread_element *te)
{
	time_t start = 0;
	unsigned i;


	g_assert(0 == te->locks.count);

	for (i = 0; te->suspend; i++) {
		te->suspended = TRUE;
		do_sched_yield();


		if G_UNLIKELY(i != 0 && 0 == i % THREAD_SUSPEND_CHECK) {
			if (0 == start)
				start = tm_time();
			if (delta_time(tm_time_exact(), start) > THREAD_SUSPEND_TIMEOUT)
				thread_timeout(te);
		}
	}

	te->suspended = FALSE;
}
