qxl_conn_get_modes(struct drm_connector *connector)
{
	int ret = 0;
	struct qxl_device *qdev = connector->dev->dev_private;
	unsigned pwidth = 1024;
	unsigned pheight = 768;

	DRM_DEBUG_KMS("monitors_config=%p\n", qdev->monitors_config);


	if (qdev->monitors_config && qdev->monitors_config->count) {
		ret = qxl_add_monitors_config_modes(connector, &pwidth, &pheight);
		if (ret < 0)
			return ret;
	}
	ret += qxl_add_common_modes(connector, pwidth, pheight);
	return ret;
}
