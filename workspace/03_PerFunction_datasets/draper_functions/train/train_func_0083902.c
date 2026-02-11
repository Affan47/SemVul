gen6_pm_iir(struct drm_i915_private *dev_priv)
{
	return INTEL_INFO(dev_priv)->gen >= 8 ? GEN8_GT_IIR(2) : GEN6_PMIIR;
}
