nv04_display_init(struct drm_device *dev)
{
	struct drm_encoder *encoder;
	struct drm_crtc *crtc;


	list_for_each_entry(encoder, &dev->mode_config.encoder_list, head) {
		const struct drm_encoder_helper_funcs *func = encoder->helper_private;

		func->restore(encoder);
	}

	list_for_each_entry(crtc, &dev->mode_config.crtc_list, head)
		crtc->funcs->restore(crtc);

	return 0;
}
