nouveau_display_vblank_enable(struct drm_device *dev, unsigned int pipe)
{
	struct drm_crtc *crtc;
	list_for_each_entry(crtc, &dev->mode_config.crtc_list, head) {
		struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
		if (nv_crtc->index == pipe) {
			nvif_notify_get(&nv_crtc->vblank);
			return 0;
		}
	}
	return -EINVAL;
}
