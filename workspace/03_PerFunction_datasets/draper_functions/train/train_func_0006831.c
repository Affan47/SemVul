intel_power_domains_suspend(struct drm_i915_private *dev_priv)
{


	if (!i915.disable_power_well)
		intel_display_power_put(dev_priv, POWER_DOMAIN_INIT);

	if (IS_SKYLAKE(dev_priv) || IS_KABYLAKE(dev_priv))
		skl_display_core_uninit(dev_priv);
	else if (IS_BROXTON(dev_priv))
		bxt_display_core_uninit(dev_priv);
}
