intel_ring_init_seqno(struct intel_engine_cs *ring, u32 seqno)
{
	struct drm_device *dev = ring->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (INTEL_INFO(dev)->gen == 6 || INTEL_INFO(dev)->gen == 7) {
		I915_WRITE(RING_SYNC_0(ring->mmio_base), 0);
		I915_WRITE(RING_SYNC_1(ring->mmio_base), 0);
		if (HAS_VEBOX(dev))
			I915_WRITE(RING_SYNC_2(ring->mmio_base), 0);
	}

	ring->set_seqno(ring, seqno);
	ring->hangcheck.seqno = seqno;
}
