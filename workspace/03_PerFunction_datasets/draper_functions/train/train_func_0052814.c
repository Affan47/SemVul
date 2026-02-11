atombios_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

	switch (mode) {
	case DRM_MODE_DPMS_ON:
		radeon_crtc->enabled = true;
		atombios_enable_crtc(crtc, ATOM_ENABLE);
		if (ASIC_IS_DCE3(rdev) && !ASIC_IS_DCE6(rdev))
			atombios_enable_crtc_memreq(crtc, ATOM_ENABLE);
		atombios_blank_crtc(crtc, ATOM_DISABLE);
		drm_vblank_post_modeset(dev, radeon_crtc->crtc_id);

		radeon_irq_set(rdev);
		radeon_crtc_load_lut(crtc);
		break;
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
	case DRM_MODE_DPMS_OFF:
		drm_vblank_pre_modeset(dev, radeon_crtc->crtc_id);
		if (radeon_crtc->enabled)
			atombios_blank_crtc(crtc, ATOM_ENABLE);
		if (ASIC_IS_DCE3(rdev) && !ASIC_IS_DCE6(rdev))
			atombios_enable_crtc_memreq(crtc, ATOM_DISABLE);
		atombios_enable_crtc(crtc, ATOM_DISABLE);
		radeon_crtc->enabled = false;
		break;
	}

	radeon_pm_compute_clocks(rdev);
}
