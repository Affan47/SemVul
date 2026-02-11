rtc_timer_remove(struct rtc_device *rtc, struct rtc_timer *timer)
{
	struct timerqueue_node *next = timerqueue_getnext(&rtc->timerqueue);
	timerqueue_del(&rtc->timerqueue, &timer->node);
	timer->enabled = 0;
	if (next == &timer->node) {
		struct rtc_wkalrm alarm;
		int err;
		next = timerqueue_getnext(&rtc->timerqueue);
		if (!next) {
			rtc_alarm_disable(rtc);
			return;
		}
		alarm.time = rtc_ktime_to_tm(next->expires);
		alarm.enabled = 1;
		err = __rtc_set_alarm(rtc, &alarm);
		if (err == -ETIME) {
			pm_stay_awake(rtc->dev.parent);
			schedule_work(&rtc->irqwork);
		}
	}
}
