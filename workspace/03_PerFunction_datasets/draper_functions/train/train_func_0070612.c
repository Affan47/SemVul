gen8_rcs_signal(struct drm_i915_gem_request *signaller_req,
			   unsigned int num_dwords)
{
#define MBOX_UPDATE_DWORDS 8
	struct intel_engine_cs *signaller = signaller_req->engine;
	struct drm_device *dev = signaller->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_engine_cs *waiter;
	enum intel_engine_id id;
	int ret, num_rings;

	num_rings = hweight32(INTEL_INFO(dev)->ring_mask);
	num_dwords += (num_rings-1) * MBOX_UPDATE_DWORDS;
#undef MBOX_UPDATE_DWORDS

	ret = intel_ring_begin(signaller_req, num_dwords);
	if (ret)
		return ret;

	for_each_engine_id(waiter, dev_priv, id) {
		u32 seqno;
		u64 gtt_offset = signaller->semaphore.signal_ggtt[id];
		if (gtt_offset == MI_SEMAPHORE_SYNC_INVALID)
			continue;

		seqno = i915_gem_request_get_seqno(signaller_req);
		intel_ring_emit(signaller, GFX_OP_PIPE_CONTROL(6));
		intel_ring_emit(signaller, PIPE_CONTROL_GLOBAL_GTT_IVB |
					   PIPE_CONTROL_QW_WRITE |
					   PIPE_CONTROL_FLUSH_ENABLE);
		intel_ring_emit(signaller, lower_32_bits(gtt_offset));
		intel_ring_emit(signaller, upper_32_bits(gtt_offset));
		intel_ring_emit(signaller, seqno);
		intel_ring_emit(signaller, 0);
		intel_ring_emit(signaller, MI_SEMAPHORE_SIGNAL |
					   MI_SEMAPHORE_TARGET(waiter->hw_id));
		intel_ring_emit(signaller, 0);
	}

	return 0;
}
