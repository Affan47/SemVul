intel_overlay_on(struct intel_overlay *overlay)
{
	struct drm_device *dev = overlay->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_engine_cs *ring = &dev_priv->ring[RCS];
	struct drm_i915_gem_request *req;
	int ret;

	WARN_ON(overlay->active);
	WARN_ON(IS_I830(dev) && !(dev_priv->quirks & QUIRK_PIPEA_FORCE));

	ret = i915_gem_request_alloc(ring, ring->default_context, &req);
	if (ret)
		return ret;

	ret = intel_ring_begin(req, 4);
	if (ret) {
		i915_gem_request_cancel(req);
		return ret;
	}

	overlay->active = true;

	intel_ring_emit(ring, MI_OVERLAY_FLIP | MI_OVERLAY_ON);
	intel_ring_emit(ring, overlay->flip_addr | OFC_UPDATE);
	intel_ring_emit(ring, MI_WAIT_FOR_EVENT | MI_WAIT_FOR_OVERLAY_FLIP);
	intel_ring_emit(ring, MI_NOOP);
	intel_ring_advance(ring);

	return intel_overlay_do_wait_request(overlay, req, NULL);
}
