i915_gem_reset(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_engine_cs *ring;
	int i;


	for_each_ring(ring, dev_priv, i)
		i915_gem_reset_ring_status(dev_priv, ring);

	for_each_ring(ring, dev_priv, i)
		i915_gem_reset_ring_cleanup(dev_priv, ring);

	i915_gem_context_reset(dev);

	i915_gem_restore_fences(dev);

	WARN_ON(i915_verify_lists(dev));
}
