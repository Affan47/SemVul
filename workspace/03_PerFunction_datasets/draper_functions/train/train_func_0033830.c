nouveau_connector_native_mode(struct drm_connector *connector)
{
	const struct drm_connector_helper_funcs *helper = connector->helper_private;
	struct nouveau_drm *drm = nouveau_drm(connector->dev);
	struct nouveau_connector *nv_connector = nouveau_connector(connector);
	struct drm_device *dev = connector->dev;
	struct drm_display_mode *mode, *largest = NULL;
	int high_w = 0, high_h = 0, high_v = 0;

	list_for_each_entry(mode, &nv_connector->base.probed_modes, head) {
		mode->vrefresh = drm_mode_vrefresh(mode);
		if (helper->mode_valid(connector, mode) != MODE_OK ||
		    (mode->flags & DRM_MODE_FLAG_INTERLACE))
			continue;


		if (mode->type & DRM_MODE_TYPE_PREFERRED) {
			NV_DEBUG(drm, "native mode from preferred\n");
			return drm_mode_duplicate(dev, mode);
		}


		if (mode->hdisplay < high_w)
			continue;

		if (mode->hdisplay == high_w && mode->vdisplay < high_h)
			continue;

		if (mode->hdisplay == high_w && mode->vdisplay == high_h &&
		    mode->vrefresh < high_v)
			continue;

		high_w = mode->hdisplay;
		high_h = mode->vdisplay;
		high_v = mode->vrefresh;
		largest = mode;
	}

	NV_DEBUG(drm, "native mode from largest: %dx%d@%d\n",
		      high_w, high_h, high_v);
	return largest ? drm_mode_duplicate(dev, largest) : NULL;
}
