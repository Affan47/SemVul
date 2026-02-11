gen6_sanitize_rps_pm_mask(struct drm_i915_private *dev_priv, u32 mask)
{


	if (INTEL_INFO(dev_priv)->gen <= 7 && !IS_HASWELL(dev_priv))
		mask &= ~GEN6_PM_RP_UP_EI_EXPIRED;

	if (INTEL_INFO(dev_priv)->gen >= 8)
		mask &= ~GEN8_PMINTR_REDIRECT_TO_NON_DISP;

	return mask;
}
