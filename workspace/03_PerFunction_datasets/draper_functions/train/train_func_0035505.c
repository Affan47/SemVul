__intel_uncore_forcewake_get(struct drm_i915_private *dev_priv,
					 enum forcewake_domains fw_domains)
{
	struct intel_uncore_forcewake_domain *domain;
	enum forcewake_domain_id id;

	if (!dev_priv->uncore.funcs.force_wake_get)
		return;

	fw_domains &= dev_priv->uncore.fw_domains;

	for_each_fw_domain_mask(domain, fw_domains, dev_priv, id) {
		if (domain->wake_count++)
			fw_domains &= ~(1 << id);
	}

	if (fw_domains)
		dev_priv->uncore.funcs.force_wake_get(dev_priv, fw_domains);
}
