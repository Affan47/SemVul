rtc_initialize_alarm(struct rtc_device *rtc, struct rtc_wkalrm *alarm)
{
	int err;
	struct rtc_time now;

	err = rtc_valid_tm(&alarm->time);
	if (err != 0)
		return err;

	err = rtc_read_time(rtc, &now);
	if (err)
		return err;

	err = mutex_lock_interruptible(&rtc->ops_lock);
	if (err)
		return err;

	rtc->aie_timer.node.expires = rtc_tm_to_ktime(alarm->time);
	rtc->aie_timer.period = ktime_set(0, 0);


	if (alarm->enabled && (rtc_tm_to_ktime(now).tv64 <
			 rtc->aie_timer.node.expires.tv64)) {

		rtc->aie_timer.enabled = 1;
		timerqueue_add(&rtc->timerqueue, &rtc->aie_timer.node);
	}
	mutex_unlock(&rtc->ops_lock);
	return err;
}
