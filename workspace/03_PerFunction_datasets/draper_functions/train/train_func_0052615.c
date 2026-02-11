ci_construct_voltage_tables(struct amdgpu_device *adev)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	int ret;

	if (pi->voltage_control == CISLANDS_VOLTAGE_CONTROL_BY_GPIO) {
		ret = amdgpu_atombios_get_voltage_table(adev, VOLTAGE_TYPE_VDDC,
							VOLTAGE_OBJ_GPIO_LUT,
							&pi->vddc_voltage_table);
		if (ret)
			return ret;
	} else if (pi->voltage_control == CISLANDS_VOLTAGE_CONTROL_BY_SVID2) {
		ret = ci_get_svi2_voltage_table(adev,
						&adev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
						&pi->vddc_voltage_table);
		if (ret)
			return ret;
	}

	if (pi->vddc_voltage_table.count > SMU7_MAX_LEVELS_VDDC)
		ci_trim_voltage_table_to_fit_state_table(adev, SMU7_MAX_LEVELS_VDDC,
							 &pi->vddc_voltage_table);

	if (pi->vddci_control == CISLANDS_VOLTAGE_CONTROL_BY_GPIO) {
		ret = amdgpu_atombios_get_voltage_table(adev, VOLTAGE_TYPE_VDDCI,
							VOLTAGE_OBJ_GPIO_LUT,
							&pi->vddci_voltage_table);
		if (ret)
			return ret;
	} else if (pi->vddci_control == CISLANDS_VOLTAGE_CONTROL_BY_SVID2) {
		ret = ci_get_svi2_voltage_table(adev,
						&adev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
						&pi->vddci_voltage_table);
		if (ret)
			return ret;
	}

	if (pi->vddci_voltage_table.count > SMU7_MAX_LEVELS_VDDCI)
		ci_trim_voltage_table_to_fit_state_table(adev, SMU7_MAX_LEVELS_VDDCI,
							 &pi->vddci_voltage_table);

	if (pi->mvdd_control == CISLANDS_VOLTAGE_CONTROL_BY_GPIO) {
		ret = amdgpu_atombios_get_voltage_table(adev, VOLTAGE_TYPE_MVDDC,
							VOLTAGE_OBJ_GPIO_LUT,
							&pi->mvdd_voltage_table);
		if (ret)
			return ret;
	} else if (pi->mvdd_control == CISLANDS_VOLTAGE_CONTROL_BY_SVID2) {
		ret = ci_get_svi2_voltage_table(adev,
						&adev->pm.dpm.dyn_state.mvdd_dependency_on_mclk,
						&pi->mvdd_voltage_table);
		if (ret)
			return ret;
	}

	if (pi->mvdd_voltage_table.count > SMU7_MAX_LEVELS_MVDD)
		ci_trim_voltage_table_to_fit_state_table(adev, SMU7_MAX_LEVELS_MVDD,
							 &pi->mvdd_voltage_table);

	return 0;
}
