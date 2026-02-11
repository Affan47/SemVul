ci_fan_ctrl_start_smc_fan_control(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	PPSMC_Result ret;

	if (pi->caps_od_fuzzy_fan_control_support) {
		ret = ci_send_msg_to_smc_with_parameter(rdev,
							PPSMC_StartFanControl,
							FAN_CONTROL_FUZZY);
		if (ret != PPSMC_Result_OK)
			return -EINVAL;
		ret = ci_send_msg_to_smc_with_parameter(rdev,
							PPSMC_MSG_SetFanPwmMax,
							rdev->pm.dpm.fan.default_max_fan_pwm);
		if (ret != PPSMC_Result_OK)
			return -EINVAL;
	} else {
		ret = ci_send_msg_to_smc_with_parameter(rdev,
							PPSMC_StartFanControl,
							FAN_CONTROL_TABLE);
		if (ret != PPSMC_Result_OK)
			return -EINVAL;
	}

	pi->fan_is_controlled_by_smc = true;
	return 0;
}
