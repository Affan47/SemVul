mi_set_context(struct drm_i915_gem_request *req, u32 hw_flags)
{
	struct intel_engine_cs *ring = req->ring;
	u32 flags = hw_flags | MI_MM_SPACE_GTT;
	const int num_rings =

		i915_semaphore_is_enabled(ring->dev) ?
		hweight32(INTEL_INFO(ring->dev)->ring_mask) - 1 :
		0;
	int len, i, ret;


	if (IS_GEN6(ring->dev)) {
		ret = ring->flush(req, I915_GEM_GPU_DOMAINS, 0);
		if (ret)
			return ret;
	}


	if (IS_HASWELL(ring->dev) || INTEL_INFO(ring->dev)->gen >= 8)
		flags |= (HSW_MI_RS_SAVE_STATE_EN | HSW_MI_RS_RESTORE_STATE_EN);
	else if (INTEL_INFO(ring->dev)->gen < 8)
		flags |= (MI_SAVE_EXT_STATE_EN | MI_RESTORE_EXT_STATE_EN);


	len = 4;
	if (INTEL_INFO(ring->dev)->gen >= 7)
		len += 2 + (num_rings ? 4*num_rings + 2 : 0);

	ret = intel_ring_begin(req, len);
	if (ret)
		return ret;


	if (INTEL_INFO(ring->dev)->gen >= 7) {
		intel_ring_emit(ring, MI_ARB_ON_OFF | MI_ARB_DISABLE);
		if (num_rings) {
			struct intel_engine_cs *signaller;

			intel_ring_emit(ring, MI_LOAD_REGISTER_IMM(num_rings));
			for_each_ring(signaller, to_i915(ring->dev), i) {
				if (signaller == ring)
					continue;

				intel_ring_emit(ring, RING_PSMI_CTL(signaller->mmio_base));
				intel_ring_emit(ring, _MASKED_BIT_ENABLE(GEN6_PSMI_SLEEP_MSG_DISABLE));
			}
		}
	}

	intel_ring_emit(ring, MI_NOOP);
	intel_ring_emit(ring, MI_SET_CONTEXT);
	intel_ring_emit(ring, i915_gem_obj_ggtt_offset(req->ctx->legacy_hw_ctx.rcs_state) |
			flags);


	intel_ring_emit(ring, MI_NOOP);

	if (INTEL_INFO(ring->dev)->gen >= 7) {
		if (num_rings) {
			struct intel_engine_cs *signaller;

			intel_ring_emit(ring, MI_LOAD_REGISTER_IMM(num_rings));
			for_each_ring(signaller, to_i915(ring->dev), i) {
				if (signaller == ring)
					continue;

				intel_ring_emit(ring, RING_PSMI_CTL(signaller->mmio_base));
				intel_ring_emit(ring, _MASKED_BIT_DISABLE(GEN6_PSMI_SLEEP_MSG_DISABLE));
			}
		}
		intel_ring_emit(ring, MI_ARB_ON_OFF | MI_ARB_ENABLE);
	}

	intel_ring_advance(ring);

	return ret;
}
