__touch_watchdog(void)
{
	__this_cpu_write(watchdog_touch_ts, get_timestamp());
}
