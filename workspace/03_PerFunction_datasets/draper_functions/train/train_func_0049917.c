radeon_pm_compute_clocks_dpm(struct radeon_device *rdev)
{
	struct drm_device *ddev = rdev->ddev;
	struct drm_crtc *crtc;
	struct radeon_crtc *radeon_crtc;

	if (!rdev->pm.dpm_enabled)
		return;

	mutex_lock(&rdev->pm.mutex);


	rdev->pm.dpm.new_active_crtcs = 0;
	rdev->pm.dpm.new_active_crtc_count = 0;
	if (rdev->num_crtc && rdev->mode_info.mode_config_initialized) {
		list_for_each_entry(crtc,
				    &ddev->mode_config.crtc_list, head) {
			radeon_crtc = to_radeon_crtc(crtc);
			if (crtc->enabled) {
				rdev->pm.dpm.new_active_crtcs |= (1 << radeon_crtc->crtc_id);
				rdev->pm.dpm.new_active_crtc_count++;
			}
		}
	}


	if (power_supply_is_system_supplied() > 0)
		rdev->pm.dpm.ac_power = true;
	else
		rdev->pm.dpm.ac_power = false;

	radeon_dpm_change_power_state_locked(rdev);

	mutex_unlock(&rdev->pm.mutex);

}
