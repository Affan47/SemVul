i830_dispatch_execbuffer(struct drm_i915_gem_request *req,
			 u64 offset, u32 len,
			 unsigned dispatch_flags)
{
	struct intel_engine_cs *ring = req->ring;
	u32 cs_offset = ring->scratch.gtt_offset;
	int ret;

	ret = intel_ring_begin(req, 6);
	if (ret)
		return ret;


	intel_ring_emit(ring, COLOR_BLT_CMD | BLT_WRITE_RGBA);
	intel_ring_emit(ring, BLT_DEPTH_32 | BLT_ROP_COLOR_COPY | 4096);
	intel_ring_emit(ring, I830_TLB_ENTRIES << 16 | 4);
	intel_ring_emit(ring, cs_offset);
	intel_ring_emit(ring, 0xdeadbeef);
	intel_ring_emit(ring, MI_NOOP);
	intel_ring_advance(ring);

	if ((dispatch_flags & I915_DISPATCH_PINNED) == 0) {
		if (len > I830_BATCH_LIMIT)
			return -ENOSPC;

		ret = intel_ring_begin(req, 6 + 2);
		if (ret)
			return ret;


		intel_ring_emit(ring, SRC_COPY_BLT_CMD | BLT_WRITE_RGBA);
		intel_ring_emit(ring, BLT_DEPTH_32 | BLT_ROP_SRC_COPY | 4096);
		intel_ring_emit(ring, DIV_ROUND_UP(len, 4096) << 16 | 4096);
		intel_ring_emit(ring, cs_offset);
		intel_ring_emit(ring, 4096);
		intel_ring_emit(ring, offset);

		intel_ring_emit(ring, MI_FLUSH);
		intel_ring_emit(ring, MI_NOOP);
		intel_ring_advance(ring);


		offset = cs_offset;
	}

	ret = intel_ring_begin(req, 4);
	if (ret)
		return ret;

	intel_ring_emit(ring, MI_BATCH_BUFFER);
	intel_ring_emit(ring, offset | (dispatch_flags & I915_DISPATCH_SECURE ?
					0 : MI_BATCH_NON_SECURE));
	intel_ring_emit(ring, offset + len - 8);
	intel_ring_emit(ring, MI_NOOP);
	intel_ring_advance(ring);

	return 0;
}
