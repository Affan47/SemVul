ci_thermal_enable_alert(struct amdgpu_device *adev,
				   bool enable)
{
	u32 thermal_int = RREG32_SMC(ixCG_THERMAL_INT);
	PPSMC_Result result;

	if (enable) {
		thermal_int &= ~(CG_THERMAL_INT_CTRL__THERM_INTH_MASK_MASK |
				 CG_THERMAL_INT_CTRL__THERM_INTL_MASK_MASK);
		WREG32_SMC(ixCG_THERMAL_INT, thermal_int);
		result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_Thermal_Cntl_Enable);
		if (result != PPSMC_Result_OK) {
			DRM_DEBUG_KMS("Could not enable thermal interrupts.\n");
			return -EINVAL;
		}
	} else {
		thermal_int |= CG_THERMAL_INT_CTRL__THERM_INTH_MASK_MASK |
			CG_THERMAL_INT_CTRL__THERM_INTL_MASK_MASK;
		WREG32_SMC(ixCG_THERMAL_INT, thermal_int);
		result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_Thermal_Cntl_Disable);
		if (result != PPSMC_Result_OK) {
			DRM_DEBUG_KMS("Could not disable thermal interrupts.\n");
			return -EINVAL;
		}
	}

	return 0;
}
