tick_sched_timer(struct hrtimer *timer)
{
	struct tick_sched *ts =
		container_of(timer, struct tick_sched, sched_timer);
	struct pt_regs *regs = get_irq_regs();
	ktime_t now = ktime_get();

	tick_sched_do_timer(now);


	if (regs)
		tick_sched_handle(ts, regs);


	if (unlikely(ts->tick_stopped))
		return HRTIMER_NORESTART;

	hrtimer_forward(timer, now, tick_period);

	return HRTIMER_RESTART;
}
