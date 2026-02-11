drm_fb_helper_add_one_connector(struct drm_fb_helper *fb_helper, struct drm_connector *connector)
{
	struct drm_fb_helper_connector **temp;
	struct drm_fb_helper_connector *fb_helper_connector;

	if (!drm_fbdev_emulation)
		return 0;

	WARN_ON(!mutex_is_locked(&fb_helper->dev->mode_config.mutex));
	if (fb_helper->connector_count + 1 > fb_helper->connector_info_alloc_count) {
		temp = krealloc(fb_helper->connector_info, sizeof(struct drm_fb_helper_connector *) * (fb_helper->connector_count + 1), GFP_KERNEL);
		if (!temp)
			return -ENOMEM;

		fb_helper->connector_info_alloc_count = fb_helper->connector_count + 1;
		fb_helper->connector_info = temp;
	}


	fb_helper_connector = kzalloc(sizeof(struct drm_fb_helper_connector), GFP_KERNEL);
	if (!fb_helper_connector)
		return -ENOMEM;

	fb_helper_connector->connector = connector;
	fb_helper->connector_info[fb_helper->connector_count++] = fb_helper_connector;
	return 0;
}
