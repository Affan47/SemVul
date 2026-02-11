ast_set_dac_reg(struct drm_crtc *crtc, struct drm_display_mode *mode,
		     struct ast_vbios_mode_info *vbios_mode)
{
	switch (crtc->primary->fb->bits_per_pixel) {
	case 8:
		break;
	default:
		return false;
	}
	return true;
}
