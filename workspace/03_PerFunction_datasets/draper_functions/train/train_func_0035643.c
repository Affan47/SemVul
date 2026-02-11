qxl_modeset_fini(struct qxl_device *qdev)
{
	qxl_fbdev_fini(qdev);

	qxl_destroy_monitors_object(qdev);
	if (qdev->mode_info.mode_config_initialized) {
		drm_mode_config_cleanup(qdev->ddev);
		qdev->mode_info.mode_config_initialized = false;
	}
}
