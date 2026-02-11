sdma_v2_4_gfx_stop(struct amdgpu_device *adev)
{
	struct amdgpu_ring *sdma0 = &adev->sdma.instance[0].ring;
	struct amdgpu_ring *sdma1 = &adev->sdma.instance[1].ring;
	u32 rb_cntl, ib_cntl;
	int i;

	if ((adev->mman.buffer_funcs_ring == sdma0) ||
	    (adev->mman.buffer_funcs_ring == sdma1))
		amdgpu_ttm_set_active_vram_size(adev, adev->mc.visible_vram_size);

	for (i = 0; i < adev->sdma.num_instances; i++) {
		rb_cntl = RREG32(mmSDMA0_GFX_RB_CNTL + sdma_offsets[i]);
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_ENABLE, 0);
		WREG32(mmSDMA0_GFX_RB_CNTL + sdma_offsets[i], rb_cntl);
		ib_cntl = RREG32(mmSDMA0_GFX_IB_CNTL + sdma_offsets[i]);
		ib_cntl = REG_SET_FIELD(ib_cntl, SDMA0_GFX_IB_CNTL, IB_ENABLE, 0);
		WREG32(mmSDMA0_GFX_IB_CNTL + sdma_offsets[i], ib_cntl);
	}
	sdma0->ready = false;
	sdma1->ready = false;
}
