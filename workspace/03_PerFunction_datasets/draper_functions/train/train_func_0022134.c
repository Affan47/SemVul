alarm_timer_set(struct k_itimer *timr, int flags,
				struct itimerspec *new_setting,
				struct itimerspec *old_setting)
{
	ktime_t exp;

	if (!rtcdev)
		return -ENOTSUPP;

	if (flags & ~TIMER_ABSTIME)
		return -EINVAL;

	if (old_setting)
		alarm_timer_get(timr, old_setting);


	if (alarm_try_to_cancel(&timr->it.alarm.alarmtimer) < 0)
		return TIMER_RETRY;


	timr->it.alarm.interval = timespec_to_ktime(new_setting->it_interval);


	if (timr->it.alarm.interval.tv64 &&
			ktime_to_ns(timr->it.alarm.interval) < TICK_NSEC)
		timr->it.alarm.interval = ktime_set(0, TICK_NSEC);

	exp = timespec_to_ktime(new_setting->it_value);

	if (flags != TIMER_ABSTIME) {
		ktime_t now;

		now = alarm_bases[timr->it.alarm.alarmtimer.type].gettime();
		exp = ktime_add_safe(now, exp);
	}

	alarm_start(&timr->it.alarm.alarmtimer, exp);
	return 0;
}
