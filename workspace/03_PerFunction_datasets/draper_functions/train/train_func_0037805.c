i915_gfx_val(struct drm_i915_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;
	unsigned long val;

	if (INTEL_INFO(dev)->gen != 5)
		return 0;

	spin_lock_irq(&mchdev_lock);

	val = __i915_gfx_val(dev_priv);

	spin_unlock_irq(&mchdev_lock);

	return val;
}
