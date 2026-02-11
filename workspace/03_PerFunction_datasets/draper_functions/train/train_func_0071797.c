intel_hpd_irq_event(struct drm_device *dev,
				struct drm_connector *connector)
{
	enum drm_connector_status old_status;

	WARN_ON(!mutex_is_locked(&dev->mode_config.mutex));
	old_status = connector->status;

	connector->status = connector->funcs->detect(connector, false);
	if (old_status == connector->status)
		return false;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s] status updated from %s to %s\n",
		      connector->base.id,
		      connector->name,
		      drm_get_connector_status_name(old_status),
		      drm_get_connector_status_name(connector->status));

	return true;
}
