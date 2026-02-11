rtc_timer_do_work(struct work_struct *work)
{
	struct rtc_timer *timer;
	struct timerqueue_node *next;
	ktime_t now;
	struct rtc_time tm;

	struct rtc_device *rtc =
		container_of(work, struct rtc_device, irqwork);

	mutex_lock(&rtc->ops_lock);
again:
	__rtc_read_time(rtc, &tm);
	now = rtc_tm_to_ktime(tm);
	while ((next = timerqueue_getnext(&rtc->timerqueue))) {
		if (next->expires.tv64 > now.tv64)
			break;


		timer = container_of(next, struct rtc_timer, node);
		timerqueue_del(&rtc->timerqueue, &timer->node);
		timer->enabled = 0;
		if (timer->task.func)
			timer->task.func(timer->task.private_data);


		if (ktime_to_ns(timer->period)) {
			timer->node.expires = ktime_add(timer->node.expires,
							timer->period);
			timer->enabled = 1;
			timerqueue_add(&rtc->timerqueue, &timer->node);
		}
	}


	if (next) {
		struct rtc_wkalrm alarm;
		int err;
		int retry = 3;

		alarm.time = rtc_ktime_to_tm(next->expires);
		alarm.enabled = 1;
reprogram:
		err = __rtc_set_alarm(rtc, &alarm);
		if (err == -ETIME)
			goto again;
		else if (err) {
			if (retry-- > 0)
				goto reprogram;

			timer = container_of(next, struct rtc_timer, node);
			timerqueue_del(&rtc->timerqueue, &timer->node);
			timer->enabled = 0;
			dev_err(&rtc->dev, "__rtc_set_alarm: err=%d\n", err);
			goto again;
		}
	} else
		rtc_alarm_disable(rtc);

	pm_relax(rtc->dev.parent);
	mutex_unlock(&rtc->ops_lock);
}
