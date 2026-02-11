radeon_dpm_single_display(struct radeon_device *rdev)
{
	bool single_display = (rdev->pm.dpm.new_active_crtc_count < 2) ?
		true : false;


	if (single_display && rdev->asic->dpm.vblank_too_short) {
		if (radeon_dpm_vblank_too_short(rdev))
			single_display = false;
	}


	if (single_display && (r600_dpm_get_vrefresh(rdev) >= 120))
		single_display = false;

	return single_display;
}
