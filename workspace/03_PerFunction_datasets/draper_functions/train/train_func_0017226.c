drm_helper_hpd_irq_event(struct drm_device *dev)
{
	struct drm_connector *connector;
	enum drm_connector_status old_status;
	bool changed = false;

	if (!dev->mode_config.poll_enabled)
		return false;

	mutex_lock(&dev->mode_config.mutex);
	drm_for_each_connector(connector, dev) {


		if (!(connector->polled & DRM_CONNECTOR_POLL_HPD))
			continue;

		old_status = connector->status;

		connector->status = connector->funcs->detect(connector, false);
		DRM_DEBUG_KMS("[CONNECTOR:%d:%s] status updated from %s to %s\n",
			      connector->base.id,
			      connector->name,
			      drm_get_connector_status_name(old_status),
			      drm_get_connector_status_name(connector->status));
		if (old_status != connector->status)
			changed = true;
	}

	mutex_unlock(&dev->mode_config.mutex);

	if (changed)
		drm_kms_helper_hotplug_event(dev);

	return changed;
}
