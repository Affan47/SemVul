ironlake_edp_pll_on(struct intel_dp *intel_dp)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_crtc *crtc = intel_dig_port->base.base.crtc;
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 dpa_ctl;

	assert_pipe_disabled(dev_priv,
			     to_intel_crtc(crtc)->pipe);

	DRM_DEBUG_KMS("\n");
	dpa_ctl = I915_READ(DP_A);
	WARN(dpa_ctl & DP_PLL_ENABLE, "dp pll on, should be off\n");
	WARN(dpa_ctl & DP_PORT_EN, "dp port still on, should be off\n");


	intel_dp->DP &= ~(DP_PORT_EN | DP_AUDIO_OUTPUT_ENABLE);
	intel_dp->DP |= DP_PLL_ENABLE;
	I915_WRITE(DP_A, intel_dp->DP);
	POSTING_READ(DP_A);
	udelay(200);
}
