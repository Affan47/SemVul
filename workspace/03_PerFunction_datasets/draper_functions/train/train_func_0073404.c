__hw_ppgtt_init(struct drm_device *dev, struct i915_hw_ppgtt *ppgtt)
{
	ppgtt->base.dev = dev;

	if (INTEL_INFO(dev)->gen < 8)
		return gen6_ppgtt_init(ppgtt);
	else
		return gen8_ppgtt_init(ppgtt);
}
