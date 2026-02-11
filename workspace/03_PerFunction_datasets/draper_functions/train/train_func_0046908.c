intel_hdmi_prepare(struct intel_encoder *encoder)
{
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *crtc = to_intel_crtc(encoder->base.crtc);
	struct intel_hdmi *intel_hdmi = enc_to_intel_hdmi(&encoder->base);
	const struct drm_display_mode *adjusted_mode = &crtc->config->base.adjusted_mode;
	u32 hdmi_val;

	hdmi_val = SDVO_ENCODING_HDMI;
	if (!HAS_PCH_SPLIT(dev) && crtc->config->limited_color_range)
		hdmi_val |= HDMI_COLOR_RANGE_16_235;
	if (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		hdmi_val |= SDVO_VSYNC_ACTIVE_HIGH;
	if (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		hdmi_val |= SDVO_HSYNC_ACTIVE_HIGH;

	if (crtc->config->pipe_bpp > 24)
		hdmi_val |= HDMI_COLOR_FORMAT_12bpc;
	else
		hdmi_val |= SDVO_COLOR_FORMAT_8bpc;

	if (crtc->config->has_hdmi_sink)
		hdmi_val |= HDMI_MODE_SELECT_HDMI;

	if (HAS_PCH_CPT(dev))
		hdmi_val |= SDVO_PIPE_SEL_CPT(crtc->pipe);
	else if (IS_CHERRYVIEW(dev))
		hdmi_val |= SDVO_PIPE_SEL_CHV(crtc->pipe);
	else
		hdmi_val |= SDVO_PIPE_SEL(crtc->pipe);

	I915_WRITE(intel_hdmi->hdmi_reg, hdmi_val);
	POSTING_READ(intel_hdmi->hdmi_reg);
}
