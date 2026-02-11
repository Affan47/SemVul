intel_dp_get_config(struct intel_encoder *encoder,
				struct intel_crtc_state *pipe_config)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	u32 tmp, flags = 0;
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	enum port port = dp_to_dig_port(intel_dp)->port;
	struct intel_crtc *crtc = to_intel_crtc(encoder->base.crtc);

	tmp = I915_READ(intel_dp->output_reg);

	pipe_config->has_audio = tmp & DP_AUDIO_OUTPUT_ENABLE && port != PORT_A;

	if (HAS_PCH_CPT(dev) && port != PORT_A) {
		u32 trans_dp = I915_READ(TRANS_DP_CTL(crtc->pipe));

		if (trans_dp & TRANS_DP_HSYNC_ACTIVE_HIGH)
			flags |= DRM_MODE_FLAG_PHSYNC;
		else
			flags |= DRM_MODE_FLAG_NHSYNC;

		if (trans_dp & TRANS_DP_VSYNC_ACTIVE_HIGH)
			flags |= DRM_MODE_FLAG_PVSYNC;
		else
			flags |= DRM_MODE_FLAG_NVSYNC;
	} else {
		if (tmp & DP_SYNC_HS_HIGH)
			flags |= DRM_MODE_FLAG_PHSYNC;
		else
			flags |= DRM_MODE_FLAG_NHSYNC;

		if (tmp & DP_SYNC_VS_HIGH)
			flags |= DRM_MODE_FLAG_PVSYNC;
		else
			flags |= DRM_MODE_FLAG_NVSYNC;
	}

	pipe_config->base.adjusted_mode.flags |= flags;

	if (!HAS_PCH_SPLIT(dev) && !IS_VALLEYVIEW(dev) &&
	    !IS_CHERRYVIEW(dev) && tmp & DP_COLOR_RANGE_16_235)
		pipe_config->limited_color_range = true;

	pipe_config->has_dp_encoder = true;

	pipe_config->lane_count =
		((tmp & DP_PORT_WIDTH_MASK) >> DP_PORT_WIDTH_SHIFT) + 1;

	intel_dp_get_m_n(crtc, pipe_config);

	if (port == PORT_A) {
		if ((I915_READ(DP_A) & DP_PLL_FREQ_MASK) == DP_PLL_FREQ_162MHZ)
			pipe_config->port_clock = 162000;
		else
			pipe_config->port_clock = 270000;
	}

	pipe_config->base.adjusted_mode.crtc_clock =
		intel_dotclock_calculate(pipe_config->port_clock,
					 &pipe_config->dp_m_n);

	if (is_edp(intel_dp) && dev_priv->vbt.edp.bpp &&
	    pipe_config->pipe_bpp > dev_priv->vbt.edp.bpp) {


		DRM_DEBUG_KMS("pipe has %d bpp for eDP panel, overriding BIOS-provided max %d bpp\n",
			      pipe_config->pipe_bpp, dev_priv->vbt.edp.bpp);
		dev_priv->vbt.edp.bpp = pipe_config->pipe_bpp;
	}
}
