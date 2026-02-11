i915_gem_reset(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_engine_cs *engine;


	for_each_engine(engine, dev_priv)
		i915_gem_reset_engine_status(dev_priv, engine);

	for_each_engine(engine, dev_priv)
		i915_gem_reset_engine_cleanup(dev_priv, engine);

	i915_gem_context_reset(dev);

	i915_gem_restore_fences(dev);

	WARN_ON(i915_verify_lists(dev));
}
