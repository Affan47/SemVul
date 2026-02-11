pm_schedule_suspend(struct device *dev, unsigned int delay)
{
	unsigned long flags;
	int retval;

	spin_lock_irqsave(&dev->power.lock, flags);

	if (!delay) {
		retval = rpm_suspend(dev, RPM_ASYNC);
		goto out;
	}

	retval = rpm_check_suspend_allowed(dev);
	if (retval)
		goto out;


	pm_runtime_cancel_pending(dev);

	dev->power.timer_expires = jiffies + msecs_to_jiffies(delay);
	dev->power.timer_expires += !dev->power.timer_expires;
	dev->power.timer_autosuspends = 0;
	mod_timer(&dev->power.suspend_timer, dev->power.timer_expires);

 out:
	spin_unlock_irqrestore(&dev->power.lock, flags);

	return retval;
}
