update_ts_time_stats(int cpu, struct tick_sched *ts, ktime_t now, u64 *last_update_time)
{
	ktime_t delta;

	if (ts->idle_active) {
		delta = ktime_sub(now, ts->idle_entrytime);
		if (nr_iowait_cpu(cpu) > 0)
			ts->iowait_sleeptime = ktime_add(ts->iowait_sleeptime, delta);
		else
			ts->idle_sleeptime = ktime_add(ts->idle_sleeptime, delta);
		ts->idle_entrytime = now;
	}

	if (last_update_time)
		*last_update_time = ktime_to_us(now);

}
