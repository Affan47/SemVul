radeon_hotplug_work_func(struct work_struct *work)
{
	struct radeon_device *rdev = container_of(work, struct radeon_device,
						  hotplug_work.work);
	struct drm_device *dev = rdev->ddev;
	struct drm_mode_config *mode_config = &dev->mode_config;
	struct drm_connector *connector;


	if (!rdev->mode_info.mode_config_initialized)
		return;

	mutex_lock(&mode_config->mutex);
	if (mode_config->num_connector) {
		list_for_each_entry(connector, &mode_config->connector_list, head)
			radeon_connector_hotplug(connector);
	}
	mutex_unlock(&mode_config->mutex);

	drm_helper_hpd_irq_event(dev);
}
