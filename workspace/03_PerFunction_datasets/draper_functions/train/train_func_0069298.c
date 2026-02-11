kv_dpm_set_power_state(struct amdgpu_device *adev)
{
	struct kv_power_info *pi = kv_get_pi(adev);
	struct amdgpu_ps *new_ps = &pi->requested_rps;
	struct amdgpu_ps *old_ps = &pi->current_rps;
	int ret;

	if (pi->bapm_enable) {
		ret = amdgpu_kv_smc_bapm_enable(adev, adev->pm.dpm.ac_power);
		if (ret) {
			DRM_ERROR("amdgpu_kv_smc_bapm_enable failed\n");
			return ret;
		}
	}

	if (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS) {
		if (pi->enable_dpm) {
			kv_set_valid_clock_range(adev, new_ps);
			kv_update_dfs_bypass_settings(adev, new_ps);
			ret = kv_calculate_ds_divider(adev);
			if (ret) {
				DRM_ERROR("kv_calculate_ds_divider failed\n");
				return ret;
			}
			kv_calculate_nbps_level_settings(adev);
			kv_calculate_dpm_settings(adev);
			kv_force_lowest_valid(adev);
			kv_enable_new_levels(adev);
			kv_upload_dpm_settings(adev);
			kv_program_nbps_index_settings(adev, new_ps);
			kv_unforce_levels(adev);
			kv_set_enabled_levels(adev);
			kv_force_lowest_valid(adev);
			kv_unforce_levels(adev);

			ret = kv_update_vce_dpm(adev, new_ps, old_ps);
			if (ret) {
				DRM_ERROR("kv_update_vce_dpm failed\n");
				return ret;
			}
			kv_update_sclk_t(adev);
			if (adev->asic_type == CHIP_MULLINS)
				kv_enable_nb_dpm(adev, true);
		}
	} else {
		if (pi->enable_dpm) {
			kv_set_valid_clock_range(adev, new_ps);
			kv_update_dfs_bypass_settings(adev, new_ps);
			ret = kv_calculate_ds_divider(adev);
			if (ret) {
				DRM_ERROR("kv_calculate_ds_divider failed\n");
				return ret;
			}
			kv_calculate_nbps_level_settings(adev);
			kv_calculate_dpm_settings(adev);
			kv_freeze_sclk_dpm(adev, true);
			kv_upload_dpm_settings(adev);
			kv_program_nbps_index_settings(adev, new_ps);
			kv_freeze_sclk_dpm(adev, false);
			kv_set_enabled_levels(adev);
			ret = kv_update_vce_dpm(adev, new_ps, old_ps);
			if (ret) {
				DRM_ERROR("kv_update_vce_dpm failed\n");
				return ret;
			}
			kv_update_acp_boot_level(adev);
			kv_update_sclk_t(adev);
			kv_enable_nb_dpm(adev, true);
		}
	}

	return 0;
}
