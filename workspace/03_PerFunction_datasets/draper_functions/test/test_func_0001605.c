drm_primary_helper_update(struct drm_plane *plane, struct drm_crtc *crtc,
			      struct drm_framebuffer *fb,
			      int crtc_x, int crtc_y,
			      unsigned int crtc_w, unsigned int crtc_h,
			      uint32_t src_x, uint32_t src_y,
			      uint32_t src_w, uint32_t src_h)
{
	struct drm_mode_set set = {
		.crtc = crtc,
		.fb = fb,
		.mode = &crtc->mode,
		.x = src_x >> 16,
		.y = src_y >> 16,
	};
	struct drm_rect src = {
		.x1 = src_x,
		.y1 = src_y,
		.x2 = src_x + src_w,
		.y2 = src_y + src_h,
	};
	struct drm_rect dest = {
		.x1 = crtc_x,
		.y1 = crtc_y,
		.x2 = crtc_x + crtc_w,
		.y2 = crtc_y + crtc_h,
	};
	const struct drm_rect clip = {
		.x2 = crtc->mode.hdisplay,
		.y2 = crtc->mode.vdisplay,
	};
	struct drm_connector **connector_list;
	int num_connectors, ret;
	bool visible;

	ret = drm_plane_helper_check_update(plane, crtc, fb,
					    &src, &dest, &clip,
					    DRM_PLANE_HELPER_NO_SCALING,
					    DRM_PLANE_HELPER_NO_SCALING,
					    false, false, &visible);
	if (ret)
		return ret;

	if (!visible)


		return plane->funcs->disable_plane(plane);


	num_connectors = get_connectors_for_crtc(crtc, NULL, 0);
	BUG_ON(num_connectors == 0);
	connector_list = kzalloc(num_connectors * sizeof(*connector_list),
				 GFP_KERNEL);
	if (!connector_list)
		return -ENOMEM;
	get_connectors_for_crtc(crtc, connector_list, num_connectors);

	set.connectors = connector_list;
	set.num_connectors = num_connectors;


	ret = crtc->funcs->set_config(&set);

	kfree(connector_list);
	return ret;
}
