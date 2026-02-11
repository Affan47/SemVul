check_overlay_possible_on_crtc(struct intel_overlay *overlay,
					  struct intel_crtc *crtc)
{
	if (!crtc->active)
		return -EINVAL;


	if (crtc->config->double_wide)
		return -EINVAL;

	return 0;
}
