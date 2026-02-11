intel_cleanup_gt_powersave(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (IS_CHERRYVIEW(dev))
		return;
	else if (IS_VALLEYVIEW(dev))
		valleyview_cleanup_gt_powersave(dev);

	if (!i915.enable_rc6)
		intel_runtime_pm_put(dev_priv);
}
