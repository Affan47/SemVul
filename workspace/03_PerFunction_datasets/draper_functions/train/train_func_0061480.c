default_stop_ok(struct device *dev)
{
	struct gpd_timing_data *td = &dev_gpd_data(dev)->td;
	unsigned long flags;
	s64 constraint_ns;

	dev_dbg(dev, "%s()\n", __func__);

	spin_lock_irqsave(&dev->power.lock, flags);

	if (!td->constraint_changed) {
		bool ret = td->cached_stop_ok;

		spin_unlock_irqrestore(&dev->power.lock, flags);
		return ret;
	}
	td->constraint_changed = false;
	td->cached_stop_ok = false;
	td->effective_constraint_ns = -1;
	constraint_ns = __dev_pm_qos_read_value(dev);

	spin_unlock_irqrestore(&dev->power.lock, flags);

	if (constraint_ns < 0)
		return false;

	constraint_ns *= NSEC_PER_USEC;


	if (!dev->power.ignore_children)
		device_for_each_child(dev, &constraint_ns,
				      dev_update_qos_constraint);

	if (constraint_ns > 0) {
		constraint_ns -= td->suspend_latency_ns +
				td->resume_latency_ns;
		if (constraint_ns == 0)
			return false;
	}
	td->effective_constraint_ns = constraint_ns;
	td->cached_stop_ok = constraint_ns >= 0;


	return td->cached_stop_ok;
}
