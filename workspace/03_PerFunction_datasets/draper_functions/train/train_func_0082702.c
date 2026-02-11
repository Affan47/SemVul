cdv_intel_limit(struct drm_crtc *crtc,
						 int refclk)
{
	const struct gma_limit_t *limit;
	if (gma_pipe_has_type(crtc, INTEL_OUTPUT_LVDS)) {


		if (refclk == 96000)
			limit = &cdv_intel_limits[CDV_LIMIT_SINGLE_LVDS_96];
		else
			limit = &cdv_intel_limits[CDV_LIMIT_SINGLE_LVDS_100];
	} else if (gma_pipe_has_type(crtc, INTEL_OUTPUT_DISPLAYPORT) ||
			gma_pipe_has_type(crtc, INTEL_OUTPUT_EDP)) {
		if (refclk == 27000)
			limit = &cdv_intel_limits[CDV_LIMIT_DP_27];
		else
			limit = &cdv_intel_limits[CDV_LIMIT_DP_100];
	} else {
		if (refclk == 27000)
			limit = &cdv_intel_limits[CDV_LIMIT_DAC_HDMI_27];
		else
			limit = &cdv_intel_limits[CDV_LIMIT_DAC_HDMI_96];
	}
	return limit;
}
