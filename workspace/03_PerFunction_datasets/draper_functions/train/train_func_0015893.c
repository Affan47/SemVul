idle_init(struct fmt_main *format)
{
#if defined(_POSIX_PRIORITY_SCHEDULING) && defined(SCHED_IDLE)
	struct sched_param param = {0};
#endif

	if (!idle_requested(format) || (options.flags & FLG_STDOUT))
		return;

	clk_tck_init();

#ifndef __BEOS__


	if (nice(20) == -1)
		perror("nice");
#else
	set_thread_priority(getpid(), 1);
#endif

#if defined(_POSIX_PRIORITY_SCHEDULING) && defined(SCHED_IDLE)
	use_yield = sched_setscheduler(getpid(), SCHED_IDLE, &param) != 0;
#elif defined(_POSIX_PRIORITY_SCHEDULING)
	use_yield = 1;
#endif
}
