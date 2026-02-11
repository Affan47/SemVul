pm_runtime_get_if_in_use(struct device *dev)
{
	unsigned long flags;
	int retval;

	spin_lock_irqsave(&dev->power.lock, flags);
	retval = dev->power.disable_depth > 0 ? -EINVAL :
		dev->power.runtime_status == RPM_ACTIVE
			&& atomic_inc_not_zero(&dev->power.usage_count);
	spin_unlock_irqrestore(&dev->power.lock, flags);
	return retval;
}
