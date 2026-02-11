ring_stuck(struct intel_engine_cs *engine, u64 acthd)
{
	struct drm_device *dev = engine->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	enum intel_ring_hangcheck_action ha;
	u32 tmp;

	ha = head_stuck(engine, acthd);
	if (ha != HANGCHECK_HUNG)
		return ha;

	if (IS_GEN2(dev))
		return HANGCHECK_HUNG;


	tmp = I915_READ_CTL(engine);
	if (tmp & RING_WAIT) {
		i915_handle_error(dev, 0,
				  "Kicking stuck wait on %s",
				  engine->name);
		I915_WRITE_CTL(engine, tmp);
		return HANGCHECK_KICK;
	}

	if (INTEL_INFO(dev)->gen >= 6 && tmp & RING_WAIT_SEMAPHORE) {
		switch (semaphore_passed(engine)) {
		default:
			return HANGCHECK_HUNG;
		case 1:
			i915_handle_error(dev, 0,
					  "Kicking stuck semaphore on %s",
					  engine->name);
			I915_WRITE_CTL(engine, tmp);
			return HANGCHECK_KICK;
		case 0:
			return HANGCHECK_WAIT;
		}
	}

	return HANGCHECK_HUNG;
}
