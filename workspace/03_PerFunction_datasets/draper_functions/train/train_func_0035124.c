intel_logical_ring_stop(struct intel_engine_cs *ring)
{
	struct drm_i915_private *dev_priv = ring->dev->dev_private;
	int ret;

	if (!intel_ring_initialized(ring))
		return;

	ret = intel_ring_idle(ring);
	if (ret && !i915_reset_in_progress(&to_i915(ring->dev)->gpu_error))
		DRM_ERROR("failed to quiesce %s whilst cleaning up: %d\n",
			  ring->name, ret);


	I915_WRITE_MODE(ring, _MASKED_BIT_ENABLE(STOP_RING));
	if (wait_for_atomic((I915_READ_MODE(ring) & MODE_IDLE) != 0, 1000)) {
		DRM_ERROR("%s :timed out trying to stop ring\n", ring->name);
		return;
	}
	I915_WRITE_MODE(ring, _MASKED_BIT_DISABLE(STOP_RING));
}
