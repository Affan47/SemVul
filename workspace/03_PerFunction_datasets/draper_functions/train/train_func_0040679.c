torture_shuffle(void *arg)
{
	VERBOSE_TOROUT_STRING("torture_shuffle task started");
	do {
		schedule_timeout_interruptible(shuffle_interval);
		torture_shuffle_tasks();
		torture_shutdown_absorb("torture_shuffle");
	} while (!torture_must_stop());
	torture_kthread_stopping("torture_shuffle");
	return 0;
}
