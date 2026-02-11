intel_logical_ring_cleanup(struct intel_engine_cs *ring)
{
	struct drm_i915_private *dev_priv;

	if (!intel_ring_initialized(ring))
		return;

	dev_priv = ring->dev->dev_private;

	intel_logical_ring_stop(ring);
	WARN_ON((I915_READ_MODE(ring) & MODE_IDLE) == 0);

	if (ring->cleanup)
		ring->cleanup(ring);

	i915_cmd_parser_fini_ring(ring);
	i915_gem_batch_pool_fini(&ring->batch_pool);

	if (ring->status_page.obj) {
		kunmap(sg_page(ring->status_page.obj->pages->sgl));
		ring->status_page.obj = NULL;
	}

	lrc_destroy_wa_ctx_obj(ring);
}
