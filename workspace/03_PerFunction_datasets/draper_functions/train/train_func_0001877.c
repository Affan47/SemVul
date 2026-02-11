si_populate_smc_tdp_limits(struct radeon_device *rdev,
				      struct radeon_ps *radeon_state)
{
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	struct si_power_info *si_pi = si_get_pi(rdev);

	if (ni_pi->enable_power_containment) {
		SISLANDS_SMC_STATETABLE *smc_table = &si_pi->smc_statetable;
		PP_SIslands_PAPMParameters *papm_parm;
		struct radeon_ppm_table *ppm = rdev->pm.dpm.dyn_state.ppm_table;
		u32 scaling_factor = si_get_smc_power_scaling_factor(rdev);
		u32 tdp_limit;
		u32 near_tdp_limit;
		int ret;

		if (scaling_factor == 0)
			return -EINVAL;

		memset(smc_table, 0, sizeof(SISLANDS_SMC_STATETABLE));

		ret = si_calculate_adjusted_tdp_limits(rdev,
						       false,
						       rdev->pm.dpm.tdp_adjustment,
						       &tdp_limit,
						       &near_tdp_limit);
		if (ret)
			return ret;

		smc_table->dpm2Params.TDPLimit =
			cpu_to_be32(si_scale_power_for_smc(tdp_limit, scaling_factor) * 1000);
		smc_table->dpm2Params.NearTDPLimit =
			cpu_to_be32(si_scale_power_for_smc(near_tdp_limit, scaling_factor) * 1000);
		smc_table->dpm2Params.SafePowerLimit =
			cpu_to_be32(si_scale_power_for_smc((near_tdp_limit * SISLANDS_DPM2_TDP_SAFE_LIMIT_PERCENT) / 100, scaling_factor) * 1000);

		ret = si_copy_bytes_to_smc(rdev,
					   (si_pi->state_table_start + offsetof(SISLANDS_SMC_STATETABLE, dpm2Params) +
						 offsetof(PP_SIslands_DPM2Parameters, TDPLimit)),
					   (u8 *)(&(smc_table->dpm2Params.TDPLimit)),
					   sizeof(u32) * 3,
					   si_pi->sram_end);
		if (ret)
			return ret;

		if (si_pi->enable_ppm) {
			papm_parm = &si_pi->papm_parm;
			memset(papm_parm, 0, sizeof(PP_SIslands_PAPMParameters));
			papm_parm->NearTDPLimitTherm = cpu_to_be32(ppm->dgpu_tdp);
			papm_parm->dGPU_T_Limit = cpu_to_be32(ppm->tj_max);
			papm_parm->dGPU_T_Warning = cpu_to_be32(95);
			papm_parm->dGPU_T_Hysteresis = cpu_to_be32(5);
			papm_parm->PlatformPowerLimit = 0xffffffff;
			papm_parm->NearTDPLimitPAPM = 0xffffffff;

			ret = si_copy_bytes_to_smc(rdev, si_pi->papm_cfg_table_start,
						   (u8 *)papm_parm,
						   sizeof(PP_SIslands_PAPMParameters),
						   si_pi->sram_end);
			if (ret)
				return ret;
		}
	}
	return 0;
}
