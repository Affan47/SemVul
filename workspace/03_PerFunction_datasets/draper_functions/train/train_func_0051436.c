drm_select_eld(struct drm_encoder *encoder)
{
	struct drm_connector *connector;
	struct drm_device *dev = encoder->dev;

	WARN_ON(!mutex_is_locked(&dev->mode_config.mutex));
	WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));

	drm_for_each_connector(connector, dev)
		if (connector->encoder == encoder && connector->eld[0])
			return connector;

	return NULL;
}
