intel_init_clock_gating(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (dev_priv->display.init_clock_gating)
		dev_priv->display.init_clock_gating(dev);
}
