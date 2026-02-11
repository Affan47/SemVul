nouveau_crtc_set_config(struct drm_mode_set *set)
{
	struct drm_device *dev;
	struct nouveau_drm *drm;
	int ret;
	struct drm_crtc *crtc;
	bool active = false;
	if (!set || !set->crtc)
		return -EINVAL;

	dev = set->crtc->dev;


	ret = pm_runtime_get_sync(dev->dev);
	if (ret < 0 && ret != -EACCES)
		return ret;

	ret = drm_crtc_helper_set_config(set);

	drm = nouveau_drm(dev);


	list_for_each_entry(crtc, &dev->mode_config.crtc_list, head) {
		if (crtc->enabled)
			active = true;
	}

	pm_runtime_mark_last_busy(dev->dev);


	if (active && !drm->have_disp_power_ref) {
		drm->have_disp_power_ref = true;
		return ret;
	}


	if (!active && drm->have_disp_power_ref) {
		pm_runtime_put_autosuspend(dev->dev);
		drm->have_disp_power_ref = false;
	}

	pm_runtime_put_autosuspend(dev->dev);
	return ret;
}
