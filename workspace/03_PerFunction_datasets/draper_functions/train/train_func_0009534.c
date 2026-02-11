sumo_enable_voltage_scaling(struct radeon_device *rdev, bool enable)
{
	if (enable) {
		WREG32_P(CG_DPM_VOLTAGE_CNTL, DPM_VOLTAGE_EN, ~DPM_VOLTAGE_EN);
		WREG32_P(CG_CG_VOLTAGE_CNTL, 0, ~CG_VOLTAGE_EN);
	} else {
		WREG32_P(CG_CG_VOLTAGE_CNTL, CG_VOLTAGE_EN, ~CG_VOLTAGE_EN);
		WREG32_P(CG_DPM_VOLTAGE_CNTL, 0, ~DPM_VOLTAGE_EN);
	}
}
