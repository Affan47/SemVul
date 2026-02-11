vmw_stdu_init(struct vmw_private *dev_priv, unsigned unit)
{
	struct vmw_screen_target_display_unit *stdu;
	struct drm_device *dev = dev_priv->dev;
	struct drm_connector *connector;
	struct drm_encoder *encoder;
	struct drm_crtc *crtc;


	stdu = kzalloc(sizeof(*stdu), GFP_KERNEL);
	if (!stdu)
		return -ENOMEM;

	stdu->base.unit = unit;
	crtc = &stdu->base.crtc;
	encoder = &stdu->base.encoder;
	connector = &stdu->base.connector;

	stdu->base.pref_active = (unit == 0);
	stdu->base.pref_width  = dev_priv->initial_width;
	stdu->base.pref_height = dev_priv->initial_height;
	stdu->base.is_implicit = true;

	drm_connector_init(dev, connector, &vmw_stdu_connector_funcs,
			   DRM_MODE_CONNECTOR_VIRTUAL);
	connector->status = vmw_du_connector_detect(connector, false);

	drm_encoder_init(dev, encoder, &vmw_stdu_encoder_funcs,
			 DRM_MODE_ENCODER_VIRTUAL);
	drm_mode_connector_attach_encoder(connector, encoder);
	encoder->possible_crtcs = (1 << unit);
	encoder->possible_clones = 0;

	(void) drm_connector_register(connector);

	drm_crtc_init(dev, crtc, &vmw_stdu_crtc_funcs);

	drm_mode_crtc_set_gamma_size(crtc, 256);

	drm_object_attach_property(&connector->base,
				   dev->mode_config.dirty_info_property,
				   1);

	return 0;
}
