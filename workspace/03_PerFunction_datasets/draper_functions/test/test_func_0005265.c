cx88_ir_work(struct hrtimer *timer)
{
	unsigned long missed;
	struct cx88_IR *ir = container_of(timer, struct cx88_IR, timer);

	cx88_ir_handle_key(ir);
	missed = hrtimer_forward_now(&ir->timer,
				     ktime_set(0, ir->polling * 1000000));
	if (missed > 1)
		ir_dprintk("Missed ticks %ld\n", missed - 1);

	return HRTIMER_RESTART;
}
