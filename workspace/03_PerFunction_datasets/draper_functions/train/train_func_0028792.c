intel_logical_ring_workarounds_emit(struct drm_i915_gem_request *req)
{
	int ret, i;
	struct intel_engine_cs *ring = req->ring;
	struct intel_ringbuffer *ringbuf = req->ringbuf;
	struct drm_device *dev = ring->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct i915_workarounds *w = &dev_priv->workarounds;

	if (WARN_ON_ONCE(w->count == 0))
		return 0;

	ring->gpu_caches_dirty = true;
	ret = logical_ring_flush_all_caches(req);
	if (ret)
		return ret;

	ret = intel_logical_ring_begin(req, w->count * 2 + 2);
	if (ret)
		return ret;

	intel_logical_ring_emit(ringbuf, MI_LOAD_REGISTER_IMM(w->count));
	for (i = 0; i < w->count; i++) {
		intel_logical_ring_emit(ringbuf, w->reg[i].addr);
		intel_logical_ring_emit(ringbuf, w->reg[i].value);
	}
	intel_logical_ring_emit(ringbuf, MI_NOOP);

	intel_logical_ring_advance(ringbuf);

	ring->gpu_caches_dirty = true;
	ret = logical_ring_flush_all_caches(req);
	if (ret)
		return ret;

	return 0;
}
