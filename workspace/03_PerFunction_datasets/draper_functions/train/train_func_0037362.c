tick_nohz_stop_idle(struct tick_sched *ts, ktime_t now)
{
	update_ts_time_stats(smp_processor_id(), ts, now, NULL);
	ts->idle_active = 0;

	sched_clock_idle_wakeup_event(0);
}
