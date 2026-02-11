cdv_hdmi_mode_set(struct drm_encoder *encoder,
			struct drm_display_mode *mode,
			struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct gma_encoder *gma_encoder = to_gma_encoder(encoder);
	struct mid_intel_hdmi_priv *hdmi_priv = gma_encoder->dev_priv;
	u32 hdmib;
	struct drm_crtc *crtc = encoder->crtc;
	struct gma_crtc *gma_crtc = to_gma_crtc(crtc);

	hdmib = (2 << 10);

	if (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		hdmib |= HDMI_VSYNC_ACTIVE_HIGH;
	if (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		hdmib |= HDMI_HSYNC_ACTIVE_HIGH;

	if (gma_crtc->pipe == 1)
		hdmib |= HDMIB_PIPE_B_SELECT;

	if (hdmi_priv->has_hdmi_audio) {
		hdmib |= HDMI_AUDIO_ENABLE;
		hdmib |= HDMI_NULL_PACKETS_DURING_VSYNC;
	}

	REG_WRITE(hdmi_priv->hdmi_reg, hdmib);
	REG_READ(hdmi_priv->hdmi_reg);
}
