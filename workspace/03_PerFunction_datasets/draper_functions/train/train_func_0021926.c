intel_edp_drrs_invalidate(struct drm_device *dev,
		unsigned frontbuffer_bits)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_crtc *crtc;
	enum pipe pipe;

	if (dev_priv->drrs.type == DRRS_NOT_SUPPORTED)
		return;

	cancel_delayed_work(&dev_priv->drrs.work);

	mutex_lock(&dev_priv->drrs.mutex);
	if (!dev_priv->drrs.dp) {
		mutex_unlock(&dev_priv->drrs.mutex);
		return;
	}

	crtc = dp_to_dig_port(dev_priv->drrs.dp)->base.base.crtc;
	pipe = to_intel_crtc(crtc)->pipe;

	frontbuffer_bits &= INTEL_FRONTBUFFER_ALL_MASK(pipe);
	dev_priv->drrs.busy_frontbuffer_bits |= frontbuffer_bits;


	if (frontbuffer_bits && dev_priv->drrs.refresh_rate_type == DRRS_LOW_RR)
		intel_dp_set_drrs_state(dev_priv->dev,
				dev_priv->drrs.dp->attached_connector->panel.
				fixed_mode->vrefresh);

	mutex_unlock(&dev_priv->drrs.mutex);
}
