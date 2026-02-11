semaphore_wait_to_signaller_ring(struct intel_engine_cs *engine, u32 ipehr,
				 u64 offset)
{
	struct drm_i915_private *dev_priv = engine->dev->dev_private;
	struct intel_engine_cs *signaller;

	if (INTEL_INFO(dev_priv)->gen >= 8) {
		for_each_engine(signaller, dev_priv) {
			if (engine == signaller)
				continue;

			if (offset == signaller->semaphore.signal_ggtt[engine->id])
				return signaller;
		}
	} else {
		u32 sync_bits = ipehr & MI_SEMAPHORE_SYNC_MASK;

		for_each_engine(signaller, dev_priv) {
			if(engine == signaller)
				continue;

			if (sync_bits == signaller->semaphore.mbox.wait[engine->id])
				return signaller;
		}
	}

	DRM_ERROR("No signaller ring found for ring %i, ipehr 0x%08x, offset 0x%016llx\n",
		  engine->id, ipehr, offset);

	return NULL;
}
