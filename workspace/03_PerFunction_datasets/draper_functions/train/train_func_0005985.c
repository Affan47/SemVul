intel_display_power_get_if_enabled(struct drm_i915_private *dev_priv,
					enum intel_display_power_domain domain)
{
	struct i915_power_domains *power_domains = &dev_priv->power_domains;
	bool is_enabled;

	if (!intel_runtime_pm_get_if_in_use(dev_priv))
		return false;

	mutex_lock(&power_domains->lock);

	if (__intel_display_power_is_enabled(dev_priv, domain)) {
		__intel_display_power_get_domain(dev_priv, domain);
		is_enabled = true;
	} else {
		is_enabled = false;
	}

	mutex_unlock(&power_domains->lock);

	if (!is_enabled)
		intel_runtime_pm_put(dev_priv);

	return is_enabled;
}
