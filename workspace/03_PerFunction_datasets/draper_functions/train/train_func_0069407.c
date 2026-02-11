hsw_power_well_pre_disable(struct drm_i915_private *dev_priv)
{
	if (IS_BROADWELL(dev_priv))
		gen8_irq_power_well_pre_disable(dev_priv,
						1 << PIPE_C | 1 << PIPE_B);
}
