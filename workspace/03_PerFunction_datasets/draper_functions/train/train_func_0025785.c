get_relative_time(void)
{
	int activecpu;


	activecpu = cpu_getactivecpu();
	if (activecpu >= 0)
		return cpunum_get_localtime(activecpu);


	if (callback_timer)
		return callback_timer_expire_time;


	return 0;
}
