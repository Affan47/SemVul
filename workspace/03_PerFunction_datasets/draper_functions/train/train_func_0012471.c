si_fan_ctrl_set_default_mode(struct radeon_device *rdev)
{
	struct si_power_info *si_pi = si_get_pi(rdev);
	u32 tmp;

	if (!si_pi->fan_ctrl_is_in_default_mode) {
		tmp = RREG32(CG_FDO_CTRL2) & ~FDO_PWM_MODE_MASK;
		tmp |= FDO_PWM_MODE(si_pi->fan_ctrl_default_mode);
		WREG32(CG_FDO_CTRL2, tmp);

		tmp = RREG32(CG_FDO_CTRL2) & ~TMIN_MASK;
		tmp |= TMIN(si_pi->t_min);
		WREG32(CG_FDO_CTRL2, tmp);
		si_pi->fan_ctrl_is_in_default_mode = true;
	}
}
