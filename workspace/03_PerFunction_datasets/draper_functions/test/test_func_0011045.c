intel_ddi_pre_enable(struct intel_encoder *intel_encoder)
{
	struct drm_encoder *encoder = &intel_encoder->base;
	struct drm_i915_private *dev_priv = to_i915(encoder->dev);
	struct intel_crtc *crtc = to_intel_crtc(encoder->crtc);
	enum port port = intel_ddi_get_encoder_port(intel_encoder);
	int type = intel_encoder->type;

	if (type == INTEL_OUTPUT_HDMI) {
		struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(encoder);

		intel_dp_dual_mode_set_tmds_output(intel_hdmi, true);
	}

	intel_prepare_ddi_buffer(intel_encoder);

	if (type == INTEL_OUTPUT_EDP) {
		struct intel_dp *intel_dp = enc_to_intel_dp(encoder);
		intel_edp_panel_on(intel_dp);
	}

	intel_ddi_clk_select(intel_encoder, crtc->config);

	if (type == INTEL_OUTPUT_DISPLAYPORT || type == INTEL_OUTPUT_EDP) {
		struct intel_dp *intel_dp = enc_to_intel_dp(encoder);

		intel_dp_set_link_params(intel_dp, crtc->config);

		intel_ddi_init_dp_buf_reg(intel_encoder);

		intel_dp_sink_dpms(intel_dp, DRM_MODE_DPMS_ON);
		intel_dp_start_link_train(intel_dp);
		if (port != PORT_A || INTEL_INFO(dev_priv)->gen >= 9)
			intel_dp_stop_link_train(intel_dp);
	} else if (type == INTEL_OUTPUT_HDMI) {
		struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(encoder);

		intel_hdmi->set_infoframes(encoder,
					   crtc->config->has_hdmi_sink,
					   &crtc->config->base.adjusted_mode);
	}
}
