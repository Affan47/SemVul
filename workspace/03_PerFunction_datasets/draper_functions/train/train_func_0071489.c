gfx_v8_0_select_se_sh(struct amdgpu_device *adev, u32 se_num, u32 sh_num)
{
	u32 data = REG_SET_FIELD(0, GRBM_GFX_INDEX, INSTANCE_BROADCAST_WRITES, 1);

	if ((se_num == 0xffffffff) && (sh_num == 0xffffffff)) {
		data = REG_SET_FIELD(data, GRBM_GFX_INDEX, SH_BROADCAST_WRITES, 1);
		data = REG_SET_FIELD(data, GRBM_GFX_INDEX, SE_BROADCAST_WRITES, 1);
	} else if (se_num == 0xffffffff) {
		data = REG_SET_FIELD(data, GRBM_GFX_INDEX, SH_INDEX, sh_num);
		data = REG_SET_FIELD(data, GRBM_GFX_INDEX, SE_BROADCAST_WRITES, 1);
	} else if (sh_num == 0xffffffff) {
		data = REG_SET_FIELD(data, GRBM_GFX_INDEX, SH_BROADCAST_WRITES, 1);
		data = REG_SET_FIELD(data, GRBM_GFX_INDEX, SE_INDEX, se_num);
	} else {
		data = REG_SET_FIELD(data, GRBM_GFX_INDEX, SH_INDEX, sh_num);
		data = REG_SET_FIELD(data, GRBM_GFX_INDEX, SE_INDEX, se_num);
	}
	WREG32(mmGRBM_GFX_INDEX, data);
}
