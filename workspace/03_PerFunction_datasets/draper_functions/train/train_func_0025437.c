gen8_init_common_ring(struct intel_engine_cs *ring)
{
	struct drm_device *dev = ring->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	u8 next_context_status_buffer_hw;

	lrc_setup_hardware_status_page(ring,
				ring->default_context->engine[ring->id].state);

	I915_WRITE_IMR(ring, ~(ring->irq_enable_mask | ring->irq_keep_mask));
	I915_WRITE(RING_HWSTAM(ring->mmio_base), 0xffffffff);

	if (ring->status_page.obj) {
		I915_WRITE(RING_HWS_PGA(ring->mmio_base),
			   (u32)ring->status_page.gfx_addr);
		POSTING_READ(RING_HWS_PGA(ring->mmio_base));
	}

	I915_WRITE(RING_MODE_GEN7(ring),
		   _MASKED_BIT_DISABLE(GFX_REPLAY_MODE) |
		   _MASKED_BIT_ENABLE(GFX_RUN_LIST_ENABLE));
	POSTING_READ(RING_MODE_GEN7(ring));


	next_context_status_buffer_hw = (I915_READ(RING_CONTEXT_STATUS_PTR(ring))
						   & GEN8_CSB_PTR_MASK);


	if (next_context_status_buffer_hw == GEN8_CSB_PTR_MASK)
		next_context_status_buffer_hw = (GEN8_CSB_ENTRIES - 1);

	ring->next_context_status_buffer = next_context_status_buffer_hw;
	DRM_DEBUG_DRIVER("Execlists enabled for %s\n", ring->name);

	memset(&ring->hangcheck, 0, sizeof(ring->hangcheck));

	return 0;
}
