radeon_dp_work_func(struct work_struct *work)
{
	struct radeon_device *rdev = container_of(work, struct radeon_device,
						  dp_work);
	struct drm_device *dev = rdev->ddev;
	struct drm_mode_config *mode_config = &dev->mode_config;
	struct drm_connector *connector;


	if (mode_config->num_connector) {
		list_for_each_entry(connector, &mode_config->connector_list, head)
			radeon_connector_hotplug(connector);
	}
}
