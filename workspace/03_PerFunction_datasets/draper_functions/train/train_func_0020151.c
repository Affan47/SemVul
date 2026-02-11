intel_dsi_mode_valid(struct drm_connector *connector,
		     struct drm_display_mode *mode)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);
	struct drm_display_mode *fixed_mode = intel_connector->panel.fixed_mode;
	int max_dotclk = to_i915(connector->dev)->max_dotclk_freq;

	DRM_DEBUG_KMS("\n");

	if (mode->flags & DRM_MODE_FLAG_DBLSCAN) {
		DRM_DEBUG_KMS("MODE_NO_DBLESCAN\n");
		return MODE_NO_DBLESCAN;
	}

	if (fixed_mode) {
		if (mode->hdisplay > fixed_mode->hdisplay)
			return MODE_PANEL;
		if (mode->vdisplay > fixed_mode->vdisplay)
			return MODE_PANEL;
		if (fixed_mode->clock > max_dotclk)
			return MODE_CLOCK_HIGH;
	}

	return MODE_OK;
}
