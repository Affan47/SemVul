usecs_to_scanlines(const struct drm_display_mode *adjusted_mode,
			      int usecs)
{

	if (!adjusted_mode->crtc_htotal)
		return 1;

	return DIV_ROUND_UP(usecs * adjusted_mode->crtc_clock,
			    1000 * adjusted_mode->crtc_htotal);
}
