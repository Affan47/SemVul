dpm_watchdog_set(struct dpm_watchdog *wd, struct device *dev)
{
	struct timer_list *timer = &wd->timer;

	wd->dev = dev;
	wd->tsk = current;

	init_timer_on_stack(timer);

	timer->expires = jiffies + HZ * CONFIG_DPM_WATCHDOG_TIMEOUT;
	timer->function = dpm_watchdog_handler;
	timer->data = (unsigned long)wd;
	add_timer(timer);
}
