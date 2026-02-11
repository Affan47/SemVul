kv_set_divider_value(struct amdgpu_device *adev,
				u32 index, u32 sclk)
{
	struct kv_power_info *pi = kv_get_pi(adev);
	struct atom_clock_dividers dividers;
	int ret;

	ret = amdgpu_atombios_get_clock_dividers(adev, COMPUTE_ENGINE_PLL_PARAM,
						 sclk, false, &dividers);
	if (ret)
		return ret;

	pi->graphics_level[index].SclkDid = (u8)dividers.post_div;
	pi->graphics_level[index].SclkFrequency = cpu_to_be32(sclk);

	return 0;
}
