qdev_crtc_init(struct drm_device *dev, int crtc_id)
{
	struct qxl_crtc *qxl_crtc;

	qxl_crtc = kzalloc(sizeof(struct qxl_crtc), GFP_KERNEL);
	if (!qxl_crtc)
		return -ENOMEM;

	drm_crtc_init(dev, &qxl_crtc->base, &qxl_crtc_funcs);
	qxl_crtc->index = crtc_id;
	drm_mode_crtc_set_gamma_size(&qxl_crtc->base, 256);
	drm_crtc_helper_add(&qxl_crtc->base, &qxl_crtc_helper_funcs);
	return 0;
}
