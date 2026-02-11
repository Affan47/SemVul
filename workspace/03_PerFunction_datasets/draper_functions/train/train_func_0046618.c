intel_panel_fitter_pipe(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32  pfit_control;


	if (INTEL_INFO(dev)->gen <= 3 && (IS_I830(dev) || !IS_MOBILE(dev)))
		return -1;

	pfit_control = I915_READ(PFIT_CONTROL);


	if ((pfit_control & PFIT_ENABLE) == 0)
		return -1;


	if (IS_GEN4(dev))
		return (pfit_control >> 29) & 0x3;


	return 1;
}
