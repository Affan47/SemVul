hdmi_sink_is_deep_color(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct drm_connector *connector;

	WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));


	list_for_each_entry(connector, &dev->mode_config.connector_list, head)
		if (connector->encoder == encoder)
			return connector->display_info.bpc > 8;

	return false;
}
