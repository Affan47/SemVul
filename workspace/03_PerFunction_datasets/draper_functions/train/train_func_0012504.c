kv_get_clk_bypass(struct amdgpu_device *adev, u32 clk)
{
	struct kv_power_info *pi = kv_get_pi(adev);
	u32 value;

	if (pi->caps_enable_dfs_bypass) {
		if (kv_get_clock_difference(clk, 40000) < 200)
			value = 3;
		else if (kv_get_clock_difference(clk, 30000) < 200)
			value = 2;
		else if (kv_get_clock_difference(clk, 20000) < 200)
			value = 7;
		else if (kv_get_clock_difference(clk, 15000) < 200)
			value = 6;
		else if (kv_get_clock_difference(clk, 10000) < 200)
			value = 8;
		else
			value = 0;
	} else {
		value = 0;
	}

	return value;
}
