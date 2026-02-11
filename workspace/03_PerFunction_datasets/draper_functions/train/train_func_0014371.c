intel_ddi_pre_enable(struct intel_encoder *intel_encoder)
{
	struct drm_encoder *encoder = &intel_encoder->base;
	struct drm_device *dev = encoder->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *crtc = to_intel_crtc(encoder->crtc);
	enum port port = intel_ddi_get_encoder_port(intel_encoder);
	int type = intel_encoder->type;
	int hdmi_level;

	if (type == INTEL_OUTPUT_EDP) {
		struct intel_dp *intel_dp = enc_to_intel_dp(encoder);
		intel_edp_panel_on(intel_dp);
	}

	if (IS_SKYLAKE(dev)) {
		uint32_t dpll = crtc->config->ddi_pll_sel;
		uint32_t val;


		if (type == INTEL_OUTPUT_EDP) {
			WARN_ON(dpll != SKL_DPLL0);

			val = I915_READ(DPLL_CTRL1);

			val &= ~(DPLL_CTRL1_HDMI_MODE(dpll) |
				 DPLL_CTRL1_SSC(dpll) |
				 DPLL_CTRL1_LINK_RATE_MASK(dpll));
			val |= crtc->config->dpll_hw_state.ctrl1 << (dpll * 6);

			I915_WRITE(DPLL_CTRL1, val);
			POSTING_READ(DPLL_CTRL1);
		}


		val = I915_READ(DPLL_CTRL2);

		val &= ~(DPLL_CTRL2_DDI_CLK_OFF(port) |
			DPLL_CTRL2_DDI_CLK_SEL_MASK(port));
		val |= (DPLL_CTRL2_DDI_CLK_SEL(dpll, port) |
			DPLL_CTRL2_DDI_SEL_OVERRIDE(port));

		I915_WRITE(DPLL_CTRL2, val);

	} else if (INTEL_INFO(dev)->gen < 9) {
		WARN_ON(crtc->config->ddi_pll_sel == PORT_CLK_SEL_NONE);
		I915_WRITE(PORT_CLK_SEL(port), crtc->config->ddi_pll_sel);
	}

	if (type == INTEL_OUTPUT_DISPLAYPORT || type == INTEL_OUTPUT_EDP) {
		struct intel_dp *intel_dp = enc_to_intel_dp(encoder);

		intel_dp_set_link_params(intel_dp, crtc->config);

		intel_ddi_init_dp_buf_reg(intel_encoder);

		intel_dp_sink_dpms(intel_dp, DRM_MODE_DPMS_ON);
		intel_dp_start_link_train(intel_dp);
		if (port != PORT_A || INTEL_INFO(dev)->gen >= 9)
			intel_dp_stop_link_train(intel_dp);
	} else if (type == INTEL_OUTPUT_HDMI) {
		struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(encoder);

		if (IS_BROXTON(dev)) {
			hdmi_level = dev_priv->vbt.
				ddi_port_info[port].hdmi_level_shift;
			bxt_ddi_vswing_sequence(dev, hdmi_level, port,
					INTEL_OUTPUT_HDMI);
		}
		intel_hdmi->set_infoframes(encoder,
					   crtc->config->has_hdmi_sink,
					   &crtc->config->base.adjusted_mode);
	}
}
