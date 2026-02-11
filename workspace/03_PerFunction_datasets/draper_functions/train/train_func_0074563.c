ptn3460_pre_enable(struct drm_bridge *bridge)
{
	struct ptn3460_bridge *ptn_bridge = bridge_to_ptn3460(bridge);
	int ret;

	if (ptn_bridge->enabled)
		return;

	gpiod_set_value(ptn_bridge->gpio_pd_n, 1);

	gpiod_set_value(ptn_bridge->gpio_rst_n, 0);
	usleep_range(10, 20);
	gpiod_set_value(ptn_bridge->gpio_rst_n, 1);

	if (drm_panel_prepare(ptn_bridge->panel)) {
		DRM_ERROR("failed to prepare panel\n");
		return;
	}


	msleep(90);

	ret = ptn3460_select_edid(ptn_bridge);
	if (ret)
		DRM_ERROR("Select EDID failed ret=%d\n", ret);

	ptn_bridge->enabled = true;
}
