intel_uncore_forcewake_reset(struct drm_device *dev, bool restore)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned long irqflags;
	struct intel_uncore_forcewake_domain *domain;
	int retry_count = 100;
	enum forcewake_domains fw = 0, active_domains;


	while (1) {
		active_domains = 0;

		for_each_fw_domain(domain, dev_priv) {
			if (hrtimer_cancel(&domain->timer) == 0)
				continue;

			intel_uncore_fw_release_timer(&domain->timer);
		}

		spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

		for_each_fw_domain(domain, dev_priv) {
			if (hrtimer_active(&domain->timer))
				active_domains |= domain->mask;
		}

		if (active_domains == 0)
			break;

		if (--retry_count == 0) {
			DRM_ERROR("Timed out waiting for forcewake timers to finish\n");
			break;
		}

		spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
		cond_resched();
	}

	WARN_ON(active_domains);

	for_each_fw_domain(domain, dev_priv)
		if (domain->wake_count)
			fw |= domain->mask;

	if (fw)
		dev_priv->uncore.funcs.force_wake_put(dev_priv, fw);

	fw_domains_reset(dev_priv, FORCEWAKE_ALL);

	if (restore) {
		if (fw)
			dev_priv->uncore.funcs.force_wake_get(dev_priv, fw);

		if (IS_GEN6(dev) || IS_GEN7(dev))
			dev_priv->uncore.fifo_count =
				fifo_free_entries(dev_priv);
	}

	if (!restore)
		assert_forcewakes_inactive(dev_priv);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}
