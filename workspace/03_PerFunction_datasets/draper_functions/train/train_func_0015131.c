intel_ddi_set_pipe_settings(struct drm_crtc *crtc)
{
	struct drm_i915_private *dev_priv = crtc->dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_encoder *intel_encoder = intel_ddi_get_crtc_encoder(crtc);
	enum transcoder cpu_transcoder = intel_crtc->config->cpu_transcoder;
	int type = intel_encoder->type;
	uint32_t temp;

	if (type == INTEL_OUTPUT_DISPLAYPORT || type == INTEL_OUTPUT_EDP || type == INTEL_OUTPUT_DP_MST) {
		WARN_ON(transcoder_is_dsi(cpu_transcoder));

		temp = TRANS_MSA_SYNC_CLK;
		switch (intel_crtc->config->pipe_bpp) {
		case 18:
			temp |= TRANS_MSA_6_BPC;
			break;
		case 24:
			temp |= TRANS_MSA_8_BPC;
			break;
		case 30:
			temp |= TRANS_MSA_10_BPC;
			break;
		case 36:
			temp |= TRANS_MSA_12_BPC;
			break;
		default:
			BUG();
		}
		I915_WRITE(TRANS_MSA_MISC(cpu_transcoder), temp);
	}
}
