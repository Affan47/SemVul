init_posix_cpu_timers(void)
{
	struct k_clock process = {
		.clock_getres	= process_cpu_clock_getres,
		.clock_get	= process_cpu_clock_get,
		.timer_create	= process_cpu_timer_create,
		.nsleep		= process_cpu_nsleep,
		.nsleep_restart	= process_cpu_nsleep_restart,
	};
	struct k_clock thread = {
		.clock_getres	= thread_cpu_clock_getres,
		.clock_get	= thread_cpu_clock_get,
		.timer_create	= thread_cpu_timer_create,
	};
	struct timespec ts;

	posix_timers_register_clock(CLOCK_PROCESS_CPUTIME_ID, &process);
	posix_timers_register_clock(CLOCK_THREAD_CPUTIME_ID, &thread);

	cputime_to_timespec(cputime_one_jiffy, &ts);
	onecputick = ts.tv_nsec;
	WARN_ON(ts.tv_sec != 0);

	return 0;
}
