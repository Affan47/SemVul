gfx_v7_0_hw_init(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	gfx_v7_0_gpu_init(adev);


	r = gfx_v7_0_rlc_resume(adev);
	if (r)
		return r;

	r = gfx_v7_0_cp_resume(adev);
	if (r)
		return r;

	adev->gfx.ce_ram_size = 0x8000;

	return r;
}
