si_thermal_start_thermal_controller(struct radeon_device *rdev)
{
	int ret;

	si_thermal_initialize(rdev);
	ret = si_thermal_set_temperature_range(rdev, R600_TEMP_RANGE_MIN, R600_TEMP_RANGE_MAX);
	if (ret)
		return ret;
	ret = si_thermal_enable_alert(rdev, true);
	if (ret)
		return ret;
	if (rdev->pm.dpm.fan.ucode_fan_control) {
		ret = si_halt_smc(rdev);
		if (ret)
			return ret;
		ret = si_thermal_setup_fan_table(rdev);
		if (ret)
			return ret;
		ret = si_resume_smc(rdev);
		if (ret)
			return ret;
		si_thermal_start_smc_fan_control(rdev);
	}

	return 0;
}
