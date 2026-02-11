intel_fb_obj_flush(struct drm_i915_gem_object *obj,
			bool retire, enum fb_op_origin origin)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	unsigned frontbuffer_bits;

	WARN_ON(!mutex_is_locked(&dev->struct_mutex));

	if (!obj->frontbuffer_bits)
		return;

	frontbuffer_bits = obj->frontbuffer_bits;

	if (retire) {
		mutex_lock(&dev_priv->fb_tracking.lock);

		frontbuffer_bits &= dev_priv->fb_tracking.busy_bits;

		dev_priv->fb_tracking.busy_bits &= ~frontbuffer_bits;
		mutex_unlock(&dev_priv->fb_tracking.lock);
	}

	intel_frontbuffer_flush(dev, frontbuffer_bits, origin);
}
