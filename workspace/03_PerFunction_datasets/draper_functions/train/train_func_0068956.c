gfx_v7_0_scratch_init(struct amdgpu_device *adev)
{
	int i;

	adev->gfx.scratch.num_reg = 7;
	adev->gfx.scratch.reg_base = mmSCRATCH_REG0;
	for (i = 0; i < adev->gfx.scratch.num_reg; i++) {
		adev->gfx.scratch.free[i] = true;
		adev->gfx.scratch.reg[i] = adev->gfx.scratch.reg_base + i;
	}
}
