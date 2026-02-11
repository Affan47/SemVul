ci_fan_ctrl_set_default_mode(struct amdgpu_device *adev)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	u32 tmp;

	if (!pi->fan_ctrl_is_in_default_mode) {
		tmp = RREG32_SMC(ixCG_FDO_CTRL2) & ~CG_FDO_CTRL2__FDO_PWM_MODE_MASK;
		tmp |= pi->fan_ctrl_default_mode << CG_FDO_CTRL2__FDO_PWM_MODE__SHIFT;
		WREG32_SMC(ixCG_FDO_CTRL2, tmp);

		tmp = RREG32_SMC(ixCG_FDO_CTRL2) & ~CG_FDO_CTRL2__TMIN_MASK;
		tmp |= pi->t_min << CG_FDO_CTRL2__TMIN__SHIFT;
		WREG32_SMC(ixCG_FDO_CTRL2, tmp);
		pi->fan_ctrl_is_in_default_mode = true;
	}
}
