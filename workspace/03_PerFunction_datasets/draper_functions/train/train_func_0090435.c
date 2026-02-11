intel_set_pch_fifo_underrun_reporting(struct drm_i915_private *dev_priv,
					   enum transcoder pch_transcoder,
					   bool enable)
{
	struct drm_crtc *crtc = dev_priv->pipe_to_crtc_mapping[pch_transcoder];
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	unsigned long flags;
	bool old;


	spin_lock_irqsave(&dev_priv->irq_lock, flags);

	old = !intel_crtc->pch_fifo_underrun_disabled;
	intel_crtc->pch_fifo_underrun_disabled = !enable;

	if (HAS_PCH_IBX(dev_priv))
		ibx_set_fifo_underrun_reporting(dev_priv->dev, pch_transcoder,
						enable);
	else
		cpt_set_fifo_underrun_reporting(dev_priv->dev, pch_transcoder,
						enable, old);

	spin_unlock_irqrestore(&dev_priv->irq_lock, flags);
	return old;
}
