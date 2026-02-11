drm_has_preferred_mode(struct drm_fb_helper_connector *fb_connector, int width, int height)
{
	struct drm_display_mode *mode;

	list_for_each_entry(mode, &fb_connector->connector->modes, head) {
		if (mode->hdisplay > width ||
		    mode->vdisplay > height)
			continue;
		if (mode->type & DRM_MODE_TYPE_PREFERRED)
			return mode;
	}
	return NULL;
}
