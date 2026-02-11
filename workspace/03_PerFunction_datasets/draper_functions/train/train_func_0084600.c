cpt_can_enable_serr_int(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	enum pipe pipe;
	struct intel_crtc *crtc;

	assert_spin_locked(&dev_priv->irq_lock);

	for_each_pipe(dev_priv, pipe) {
		crtc = to_intel_crtc(dev_priv->pipe_to_crtc_mapping[pipe]);

		if (crtc->pch_fifo_underrun_disabled)
			return false;
	}

	return true;
}
