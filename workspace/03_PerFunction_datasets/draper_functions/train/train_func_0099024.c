ci_thermal_set_temperature_range(struct amdgpu_device *adev,
					    int min_temp, int max_temp)
{
	int low_temp = 0 * 1000;
	int high_temp = 255 * 1000;
	u32 tmp;

	if (low_temp < min_temp)
		low_temp = min_temp;
	if (high_temp > max_temp)
		high_temp = max_temp;
	if (high_temp < low_temp) {
		DRM_ERROR("invalid thermal range: %d - %d\n", low_temp, high_temp);
		return -EINVAL;
	}

	tmp = RREG32_SMC(ixCG_THERMAL_INT);
	tmp &= ~(CG_THERMAL_INT__DIG_THERM_INTH_MASK | CG_THERMAL_INT__DIG_THERM_INTL_MASK);
	tmp |= ((high_temp / 1000) << CG_THERMAL_INT__DIG_THERM_INTH__SHIFT) |
		((low_temp / 1000)) << CG_THERMAL_INT__DIG_THERM_INTL__SHIFT;
	WREG32_SMC(ixCG_THERMAL_INT, tmp);

#if 0

	tmp = RREG32_SMC(ixCG_THERMAL_CTRL);
	tmp &= DIG_THERM_DPM_MASK;
	tmp |= DIG_THERM_DPM(high_temp / 1000);
	WREG32_SMC(ixCG_THERMAL_CTRL, tmp);
#endif

	adev->pm.dpm.thermal.min_temp = low_temp;
	adev->pm.dpm.thermal.max_temp = high_temp;
	return 0;
}
