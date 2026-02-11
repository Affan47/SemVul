ci_trim_dpm_states(struct amdgpu_device *adev,
			      struct amdgpu_ps *amdgpu_state)
{
	struct ci_ps *state = ci_get_ps(amdgpu_state);
	struct ci_power_info *pi = ci_get_pi(adev);
	u32 high_limit_count;

	if (state->performance_level_count < 1)
		return -EINVAL;

	if (state->performance_level_count == 1)
		high_limit_count = 0;
	else
		high_limit_count = 1;

	ci_trim_single_dpm_states(adev,
				  &pi->dpm_table.sclk_table,
				  state->performance_levels[0].sclk,
				  state->performance_levels[high_limit_count].sclk);

	ci_trim_single_dpm_states(adev,
				  &pi->dpm_table.mclk_table,
				  state->performance_levels[0].mclk,
				  state->performance_levels[high_limit_count].mclk);

	ci_trim_pcie_dpm_states(adev,
				state->performance_levels[0].pcie_gen,
				state->performance_levels[0].pcie_lane,
				state->performance_levels[high_limit_count].pcie_gen,
				state->performance_levels[high_limit_count].pcie_lane);

	return 0;
}
