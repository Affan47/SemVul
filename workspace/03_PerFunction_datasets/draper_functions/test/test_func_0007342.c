__intel_uncore_forcewake_put(struct drm_i915_private *dev_priv,
					 enum forcewake_domains fw_domains)
{
	struct intel_uncore_forcewake_domain *domain;
	enum forcewake_domain_id id;

	if (!dev_priv->uncore.funcs.force_wake_put)
		return;

	fw_domains &= dev_priv->uncore.fw_domains;

	for_each_fw_domain_mask(domain, fw_domains, dev_priv, id) {
		if (WARN_ON(domain->wake_count == 0))
			continue;

		if (--domain->wake_count)
			continue;

		domain->wake_count++;
		fw_domain_arm_timer(domain);
	}
}
