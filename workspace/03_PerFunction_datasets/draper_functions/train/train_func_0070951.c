intel_uncore_fw_release_timer(struct hrtimer *timer)
{
	struct intel_uncore_forcewake_domain *domain =
	       container_of(timer, struct intel_uncore_forcewake_domain, timer);
	unsigned long irqflags;

	assert_rpm_device_not_suspended(domain->i915);

	spin_lock_irqsave(&domain->i915->uncore.lock, irqflags);
	if (WARN_ON(domain->wake_count == 0))
		domain->wake_count++;

	if (--domain->wake_count == 0)
		domain->i915->uncore.funcs.force_wake_put(domain->i915,
							  1 << domain->id);

	spin_unlock_irqrestore(&domain->i915->uncore.lock, irqflags);

	return HRTIMER_NORESTART;
}
