intel_power_domains_init_hw(struct drm_i915_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;
	struct i915_power_domains *power_domains = &dev_priv->power_domains;

	power_domains->initializing = true;

	if (IS_CHERRYVIEW(dev)) {
		mutex_lock(&power_domains->lock);
		chv_phy_control_init(dev_priv);
		mutex_unlock(&power_domains->lock);
	} else if (IS_VALLEYVIEW(dev)) {
		mutex_lock(&power_domains->lock);
		vlv_cmnlane_wa(dev_priv);
		mutex_unlock(&power_domains->lock);
	}


	intel_display_set_init_power(dev_priv, true);
	intel_power_domains_resume(dev_priv);
	power_domains->initializing = false;
}
