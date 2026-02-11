cpt_set_infoframes(struct drm_encoder *encoder,
			       bool enable,
			       const struct drm_display_mode *adjusted_mode)
{
	struct drm_i915_private *dev_priv = encoder->dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(encoder->crtc);
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(encoder);
	i915_reg_t reg = TVIDEO_DIP_CTL(intel_crtc->pipe);
	u32 val = I915_READ(reg);

	assert_hdmi_port_disabled(intel_hdmi);


	val |= VIDEO_DIP_SELECT_AVI | VIDEO_DIP_FREQ_VSYNC;

	if (!enable) {
		if (!(val & VIDEO_DIP_ENABLE))
			return;
		val &= ~(VIDEO_DIP_ENABLE | VIDEO_DIP_ENABLE_AVI |
			 VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
			 VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);
		I915_WRITE(reg, val);
		POSTING_READ(reg);
		return;
	}


	val |= VIDEO_DIP_ENABLE | VIDEO_DIP_ENABLE_AVI;
	val &= ~(VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
		 VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);

	if (intel_hdmi_set_gcp_infoframe(encoder))
		val |= VIDEO_DIP_ENABLE_GCP;

	I915_WRITE(reg, val);
	POSTING_READ(reg);

	intel_hdmi_set_avi_infoframe(encoder, adjusted_mode);
	intel_hdmi_set_spd_infoframe(encoder);
	intel_hdmi_set_hdmi_infoframe(encoder, adjusted_mode);
}
