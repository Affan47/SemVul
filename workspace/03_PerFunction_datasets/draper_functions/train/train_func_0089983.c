kv_enable_didt(struct amdgpu_device *adev, bool enable)
{
	struct kv_power_info *pi = kv_get_pi(adev);
	int ret;

	if (pi->caps_sq_ramping ||
	    pi->caps_db_ramping ||
	    pi->caps_td_ramping ||
	    pi->caps_tcp_ramping) {
		gfx_v7_0_enter_rlc_safe_mode(adev);

		if (enable) {
			ret = kv_program_pt_config_registers(adev, didt_config_kv);
			if (ret) {
				gfx_v7_0_exit_rlc_safe_mode(adev);
				return ret;
			}
		}

		kv_do_enable_didt(adev, enable);

		gfx_v7_0_exit_rlc_safe_mode(adev);
	}

	return 0;
}
