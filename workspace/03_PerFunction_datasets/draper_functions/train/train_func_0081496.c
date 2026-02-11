i915_gem_cleanup_stolen(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (!drm_mm_initialized(&dev_priv->mm.stolen))
		return;

	drm_mm_takedown(&dev_priv->mm.stolen);
}
