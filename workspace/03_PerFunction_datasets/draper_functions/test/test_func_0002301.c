i915_hpd_poll_init_work(struct work_struct *work) {
	struct drm_i915_private *dev_priv =
		container_of(work, struct drm_i915_private,
			     hotplug.poll_init_work);
	struct drm_device *dev = dev_priv->dev;
	struct drm_mode_config *mode_config = &dev->mode_config;
	struct drm_connector *connector;
	bool enabled;

	mutex_lock(&dev->mode_config.mutex);

	enabled = READ_ONCE(dev_priv->hotplug.poll_enabled);

	list_for_each_entry(connector, &mode_config->connector_list, head) {
		struct intel_connector *intel_connector =
			to_intel_connector(connector);
		connector->polled = intel_connector->polled;


		if (intel_connector->mst_port)
			continue;

		if (!connector->polled && I915_HAS_HOTPLUG(dev) &&
		    intel_connector->encoder->hpd_pin > HPD_NONE) {
			connector->polled = enabled ?
				DRM_CONNECTOR_POLL_CONNECT |
				DRM_CONNECTOR_POLL_DISCONNECT :
				DRM_CONNECTOR_POLL_HPD;
		}
	}

	if (enabled)
		drm_kms_helper_poll_enable_locked(dev);

	mutex_unlock(&dev->mode_config.mutex);


	if (!enabled)
		drm_helper_hpd_irq_event(dev);
}
