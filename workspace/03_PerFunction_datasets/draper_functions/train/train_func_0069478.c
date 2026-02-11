tonga_fan_ctrl_get_fan_speed_percent(struct pp_hwmgr *hwmgr, uint32_t *speed)
{
	uint32_t duty100;
	uint32_t duty;
	uint64_t tmp64;

	if (hwmgr->thermal_controller.fanInfo.bNoFan)
		return 0;

	duty100 = PHM_READ_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, CG_FDO_CTRL1, FMAX_DUTY100);
	duty = PHM_READ_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, CG_THERMAL_STATUS, FDO_PWM_DUTY);

	if (0 == duty100)
		return -EINVAL;


	tmp64 = (uint64_t)duty * 100;
	do_div(tmp64, duty100);
	*speed = (uint32_t)tmp64;

	if (*speed > 100)
		*speed = 100;

	return 0;
}
