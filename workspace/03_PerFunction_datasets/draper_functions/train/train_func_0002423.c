alarmtimer_suspend(struct device *dev)
{
	struct rtc_time tm;
	ktime_t min, now;
	unsigned long flags;
	struct rtc_device *rtc;
	int i;
	int ret;

	spin_lock_irqsave(&freezer_delta_lock, flags);
	min = freezer_delta;
	freezer_delta = ktime_set(0, 0);
	spin_unlock_irqrestore(&freezer_delta_lock, flags);

	rtc = alarmtimer_get_rtcdev();

	if (!rtc)
		return 0;


	for (i = 0; i < ALARM_NUMTYPE; i++) {
		struct alarm_base *base = &alarm_bases[i];
		struct timerqueue_node *next;
		ktime_t delta;

		spin_lock_irqsave(&base->lock, flags);
		next = timerqueue_getnext(&base->timerqueue);
		spin_unlock_irqrestore(&base->lock, flags);
		if (!next)
			continue;
		delta = ktime_sub(next->expires, base->gettime());
		if (!min.tv64 || (delta.tv64 < min.tv64))
			min = delta;
	}
	if (min.tv64 == 0)
		return 0;

	if (ktime_to_ns(min) < 2 * NSEC_PER_SEC) {
		__pm_wakeup_event(ws, 2 * MSEC_PER_SEC);
		return -EBUSY;
	}


	rtc_timer_cancel(rtc, &rtctimer);
	rtc_read_time(rtc, &tm);
	now = rtc_tm_to_ktime(tm);
	now = ktime_add(now, min);


	ret = rtc_timer_start(rtc, &rtctimer, now, ktime_set(0, 0));
	if (ret < 0)
		__pm_wakeup_event(ws, MSEC_PER_SEC);
	return ret;
}
