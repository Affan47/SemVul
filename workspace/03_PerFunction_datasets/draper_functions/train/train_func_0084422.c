radeon_crtc_load_lut(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;

	if (!crtc->enabled)
		return;

	if (ASIC_IS_DCE5(rdev))
		dce5_crtc_load_lut(crtc);
	else if (ASIC_IS_DCE4(rdev))
		dce4_crtc_load_lut(crtc);
	else if (ASIC_IS_AVIVO(rdev))
		avivo_crtc_load_lut(crtc);
	else
		legacy_crtc_load_lut(crtc);
}
