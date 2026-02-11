intel_overlay_release_old_vid(struct intel_overlay *overlay)
{
	struct drm_device *dev = overlay->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_engine_cs *ring = &dev_priv->ring[RCS];
	int ret;

	WARN_ON(!mutex_is_locked(&dev->struct_mutex));


	if (!overlay->old_vid_bo)
		return 0;

	if (I915_READ(ISR) & I915_OVERLAY_PLANE_FLIP_PENDING_INTERRUPT) {

		struct drm_i915_gem_request *req;

		ret = i915_gem_request_alloc(ring, ring->default_context, &req);
		if (ret)
			return ret;

		ret = intel_ring_begin(req, 2);
		if (ret) {
			i915_gem_request_cancel(req);
			return ret;
		}

		intel_ring_emit(ring, MI_WAIT_FOR_EVENT | MI_WAIT_FOR_OVERLAY_FLIP);
		intel_ring_emit(ring, MI_NOOP);
		intel_ring_advance(ring);

		ret = intel_overlay_do_wait_request(overlay, req,
						    intel_overlay_release_old_vid_tail);
		if (ret)
			return ret;
	}

	intel_overlay_release_old_vid_tail(overlay);


	i915_gem_track_fb(overlay->old_vid_bo, NULL,
			  INTEL_FRONTBUFFER_OVERLAY(overlay->crtc->pipe));
	return 0;
}
