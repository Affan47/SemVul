status_store(struct device *device,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct drm_connector *connector = to_drm_connector(device);
	struct drm_device *dev = connector->dev;
	enum drm_connector_status old_status;
	int ret;

	ret = mutex_lock_interruptible(&dev->mode_config.mutex);
	if (ret)
		return ret;

	old_status = connector->status;

	if (sysfs_streq(buf, "detect")) {
		connector->force = 0;
		connector->status = connector->funcs->detect(connector, true);
	} else if (sysfs_streq(buf, "on")) {
		connector->force = DRM_FORCE_ON;
	} else if (sysfs_streq(buf, "on-digital")) {
		connector->force = DRM_FORCE_ON_DIGITAL;
	} else if (sysfs_streq(buf, "off")) {
		connector->force = DRM_FORCE_OFF;
	} else
		ret = -EINVAL;

	if (ret == 0 && connector->force) {
		if (connector->force == DRM_FORCE_ON ||
		    connector->force == DRM_FORCE_ON_DIGITAL)
			connector->status = connector_status_connected;
		else
			connector->status = connector_status_disconnected;
		if (connector->funcs->force)
			connector->funcs->force(connector);
	}

	if (old_status != connector->status) {
		DRM_DEBUG_KMS("[CONNECTOR:%d:%s] status updated from %d to %d\n",
			      connector->base.id,
			      connector->name,
			      old_status, connector->status);

		dev->mode_config.delayed_event = true;
		if (dev->mode_config.poll_enabled)
			schedule_delayed_work(&dev->mode_config.output_poll_work,
					      0);
	}

	mutex_unlock(&dev->mode_config.mutex);

	return ret ? ret : count;
}
