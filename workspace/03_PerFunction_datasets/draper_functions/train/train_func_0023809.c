intel_power_domains_sync_hw(struct drm_i915_private *dev_priv)
{
	struct i915_power_domains *power_domains = &dev_priv->power_domains;
	struct i915_power_well *power_well;
	int i;

	mutex_lock(&power_domains->lock);
	for_each_power_well(i, power_well, POWER_DOMAIN_MASK, power_domains) {
		power_well->ops->sync_hw(dev_priv, power_well);
		power_well->hw_enabled = power_well->ops->is_enabled(dev_priv,
								     power_well);
	}
	mutex_unlock(&power_domains->lock);
}
