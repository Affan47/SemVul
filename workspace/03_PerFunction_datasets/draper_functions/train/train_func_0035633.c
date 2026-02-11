intel_dp_enable_port(struct intel_dp *intel_dp)
{
	struct drm_device *dev = intel_dp_to_dev(intel_dp);
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *crtc =
		to_intel_crtc(dp_to_dig_port(intel_dp)->base.base.crtc);


	_intel_dp_set_link_train(intel_dp, &intel_dp->DP,
				 DP_TRAINING_PATTERN_1);

	I915_WRITE(intel_dp->output_reg, intel_dp->DP);
	POSTING_READ(intel_dp->output_reg);


	intel_dp->DP |= DP_PORT_EN;
	if (crtc->config->has_audio)
		intel_dp->DP |= DP_AUDIO_OUTPUT_ENABLE;

	I915_WRITE(intel_dp->output_reg, intel_dp->DP);
	POSTING_READ(intel_dp->output_reg);
}
