si_get_std_voltage_value(struct radeon_device *rdev,
				    SISLANDS_SMC_VOLTAGE_VALUE *voltage,
				    u16 *std_voltage)
{
	u16 v_index;
	bool voltage_found = false;
	*std_voltage = be16_to_cpu(voltage->value);

	if (rdev->pm.dpm.dyn_state.cac_leakage_table.entries) {
		if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_NEW_CAC_VOLTAGE) {
			if (rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries == NULL)
				return -EINVAL;

			for (v_index = 0; (u32)v_index < rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.count; v_index++) {
				if (be16_to_cpu(voltage->value) ==
				    (u16)rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[v_index].v) {
					voltage_found = true;
					if ((u32)v_index < rdev->pm.dpm.dyn_state.cac_leakage_table.count)
						*std_voltage =
							rdev->pm.dpm.dyn_state.cac_leakage_table.entries[v_index].vddc;
					else
						*std_voltage =
							rdev->pm.dpm.dyn_state.cac_leakage_table.entries[rdev->pm.dpm.dyn_state.cac_leakage_table.count-1].vddc;
					break;
				}
			}

			if (!voltage_found) {
				for (v_index = 0; (u32)v_index < rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.count; v_index++) {
					if (be16_to_cpu(voltage->value) <=
					    (u16)rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[v_index].v) {
						voltage_found = true;
						if ((u32)v_index < rdev->pm.dpm.dyn_state.cac_leakage_table.count)
							*std_voltage =
								rdev->pm.dpm.dyn_state.cac_leakage_table.entries[v_index].vddc;
						else
							*std_voltage =
								rdev->pm.dpm.dyn_state.cac_leakage_table.entries[rdev->pm.dpm.dyn_state.cac_leakage_table.count-1].vddc;
						break;
					}
				}
			}
		} else {
			if ((u32)voltage->index < rdev->pm.dpm.dyn_state.cac_leakage_table.count)
				*std_voltage = rdev->pm.dpm.dyn_state.cac_leakage_table.entries[voltage->index].vddc;
		}
	}

	return 0;
}
