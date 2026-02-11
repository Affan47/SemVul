intel_hdmi_source_max_tmds_clock(struct drm_i915_private *dev_priv)
{
	if (IS_G4X(dev_priv))
		return 165000;
	else if (IS_HASWELL(dev_priv) || INTEL_INFO(dev_priv)->gen >= 8)
		return 300000;
	else
		return 225000;
}
