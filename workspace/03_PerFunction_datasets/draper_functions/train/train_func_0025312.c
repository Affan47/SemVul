sumo_dpm_late_enable(struct radeon_device *rdev)
{
	int ret;

	ret = sumo_enable_clock_power_gating(rdev);
	if (ret)
		return ret;

	if (rdev->irq.installed &&
	    r600_is_internal_thermal_sensor(rdev->pm.int_thermal_type)) {
		ret = sumo_set_thermal_temperature_range(rdev, R600_TEMP_RANGE_MIN, R600_TEMP_RANGE_MAX);
		if (ret)
			return ret;
		rdev->irq.dpm_thermal = true;
		radeon_irq_set(rdev);
	}

	return 0;
}
