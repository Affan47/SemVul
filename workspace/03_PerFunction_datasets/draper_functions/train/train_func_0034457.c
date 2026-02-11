drm_fb_helper_restore_lut_atomic(struct drm_crtc *crtc)
{
	uint16_t *r_base, *g_base, *b_base;

	if (crtc->funcs->gamma_set == NULL)
		return;

	r_base = crtc->gamma_store;
	g_base = r_base + crtc->gamma_size;
	b_base = g_base + crtc->gamma_size;

	crtc->funcs->gamma_set(crtc, r_base, g_base, b_base, 0, crtc->gamma_size);
}
