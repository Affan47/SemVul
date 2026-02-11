cpt_check_pch_fifo_underruns(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum transcoder pch_transcoder = (enum transcoder) crtc->pipe;
	uint32_t serr_int = I915_READ(SERR_INT);

	assert_spin_locked(&dev_priv->irq_lock);

	if ((serr_int & SERR_INT_TRANS_FIFO_UNDERRUN(pch_transcoder)) == 0)
		return;

	I915_WRITE(SERR_INT, SERR_INT_TRANS_FIFO_UNDERRUN(pch_transcoder));
	POSTING_READ(SERR_INT);

	DRM_ERROR("pch fifo underrun on pch transcoder %s\n",
		  transcoder_name(pch_transcoder));
}
