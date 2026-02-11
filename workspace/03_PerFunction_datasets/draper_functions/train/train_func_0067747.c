rtc_irq_set_state(struct rtc_device *rtc, struct rtc_task *task, int enabled)
{
	int err = 0;
	unsigned long flags;

retry:
	spin_lock_irqsave(&rtc->irq_task_lock, flags);
	if (rtc->irq_task != NULL && task == NULL)
		err = -EBUSY;
	else if (rtc->irq_task != task)
		err = -EACCES;
	else {
		if (rtc_update_hrtimer(rtc, enabled) < 0) {
			spin_unlock_irqrestore(&rtc->irq_task_lock, flags);
			cpu_relax();
			goto retry;
		}
		rtc->pie_enabled = enabled;
	}
	spin_unlock_irqrestore(&rtc->irq_task_lock, flags);
	return err;
}
