rv6xx_get_master_voltage_mask(struct radeon_device *rdev)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);
	u64 master_mask = 0;
	int i;

	for (i = 0; i < R600_PM_NUMBER_OF_VOLTAGE_LEVELS; i++) {
		u32 tmp_mask, tmp_set_pins;
		int ret;

		ret = radeon_atom_get_voltage_gpio_settings(rdev,
							    pi->hw.vddc[i],
							    SET_VOLTAGE_TYPE_ASIC_VDDC,
							    &tmp_set_pins, &tmp_mask);

		if (ret == 0)
			master_mask |= tmp_mask;
	}

	return master_mask;
}
