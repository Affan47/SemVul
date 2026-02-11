intel_dsi_compute_config(struct intel_encoder *encoder,
				     struct intel_crtc_state *config)
{
	struct intel_dsi *intel_dsi = container_of(encoder, struct intel_dsi,
						   base);
	struct intel_connector *intel_connector = intel_dsi->attached_connector;
	struct drm_display_mode *fixed_mode = intel_connector->panel.fixed_mode;
	struct drm_display_mode *adjusted_mode = &config->base.adjusted_mode;

	DRM_DEBUG_KMS("\n");

	if (fixed_mode)
		intel_fixed_panel_mode(fixed_mode, adjusted_mode);


	adjusted_mode->flags = 0;

	return true;
}
