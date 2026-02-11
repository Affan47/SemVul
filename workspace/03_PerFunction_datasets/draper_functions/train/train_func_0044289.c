gpu_sync_timer(int param)
{

	if (gpu_command_pending && param < 1000)
		timer_set(TIME_IN_USEC(50), ++param, gpu_sync_timer);
}
