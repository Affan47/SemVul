tonga_set_max_fan_rpm_output(struct pp_hwmgr *hwmgr, uint16_t us_max_fan_pwm)
{
	hwmgr->thermal_controller.advanceFanControlParameters.usMaxFanRPM = us_max_fan_pwm;

	if (phm_is_hw_access_blocked(hwmgr))
		return 0;

	return (0 == smum_send_msg_to_smc_with_parameter(hwmgr->smumgr, PPSMC_MSG_SetFanRpmMax, us_max_fan_pwm) ? 0 : -1);
}
