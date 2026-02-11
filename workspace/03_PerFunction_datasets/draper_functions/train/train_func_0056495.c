any_waiters(struct drm_i915_private *dev_priv)
{
	struct intel_engine_cs *engine;

	for_each_engine(engine, dev_priv)
		if (engine->irq_refcount)
			return true;

	return false;
}
