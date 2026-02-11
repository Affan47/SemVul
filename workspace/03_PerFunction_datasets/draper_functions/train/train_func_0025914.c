si_populate_mvdd_value(struct radeon_device *rdev, u32 mclk,
				  SISLANDS_SMC_VOLTAGE_VALUE *voltage)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct si_power_info *si_pi = si_get_pi(rdev);

	if (pi->mvdd_control) {
		if (mclk <= pi->mvdd_split_frequency)
			voltage->index = 0;
		else
			voltage->index = (u8)(si_pi->mvdd_voltage_table.count) - 1;

		voltage->value = cpu_to_be16(si_pi->mvdd_voltage_table.entries[voltage->index].value);
	}
	return 0;
}
