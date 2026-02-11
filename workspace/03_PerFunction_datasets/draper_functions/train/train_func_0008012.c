pm_runtime_init(struct device *dev)
{
	dev->power.runtime_status = RPM_SUSPENDED;
	dev->power.idle_notification = false;

	dev->power.disable_depth = 1;
	atomic_set(&dev->power.usage_count, 0);

	dev->power.runtime_error = 0;

	atomic_set(&dev->power.child_count, 0);
	pm_suspend_ignore_children(dev, false);
	dev->power.runtime_auto = true;

	dev->power.request_pending = false;
	dev->power.request = RPM_REQ_NONE;
	dev->power.deferred_resume = false;
	dev->power.accounting_timestamp = jiffies;
	INIT_WORK(&dev->power.work, pm_runtime_work);

	dev->power.timer_expires = 0;
	setup_timer(&dev->power.suspend_timer, pm_suspend_timer_fn,
			(unsigned long)dev);

	init_waitqueue_head(&dev->power.wait_queue);
}
