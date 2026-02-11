drm_helper_encoder_in_use(struct drm_encoder *encoder)
{
	struct drm_connector *connector;
	struct drm_device *dev = encoder->dev;


	if (!oops_in_progress) {
		WARN_ON(!mutex_is_locked(&dev->mode_config.mutex));
		WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));
	}

	drm_for_each_connector(connector, dev)
		if (connector->encoder == encoder)
			return true;
	return false;
}
