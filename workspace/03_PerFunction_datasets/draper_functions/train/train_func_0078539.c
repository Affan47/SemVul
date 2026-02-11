pm_runtime_deactivate_timer(struct device *dev)
{
	if (dev->power.timer_expires > 0) {
		del_timer(&dev->power.suspend_timer);
		dev->power.timer_expires = 0;
	}
}
