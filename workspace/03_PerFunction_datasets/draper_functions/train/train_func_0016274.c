ibx_irq_reset(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (HAS_PCH_NOP(dev))
		return;

	GEN5_IRQ_RESET(SDE);

	if (HAS_PCH_CPT(dev) || HAS_PCH_LPT(dev))
		I915_WRITE(SERR_INT, 0xffffffff);
}
