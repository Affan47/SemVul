r100_ib_test(struct radeon_device *rdev, struct radeon_ring *ring)
{
	struct radeon_ib ib;
	uint32_t scratch;
	uint32_t tmp = 0;
	unsigned i;
	int r;

	r = radeon_scratch_get(rdev, &scratch);
	if (r) {
		DRM_ERROR("radeon: failed to get scratch reg (%d).\n", r);
		return r;
	}
	WREG32(scratch, 0xCAFEDEAD);
	r = radeon_ib_get(rdev, RADEON_RING_TYPE_GFX_INDEX, &ib, NULL, 256);
	if (r) {
		DRM_ERROR("radeon: failed to get ib (%d).\n", r);
		goto free_scratch;
	}
	ib.ptr[0] = PACKET0(scratch, 0);
	ib.ptr[1] = 0xDEADBEEF;
	ib.ptr[2] = PACKET2(0);
	ib.ptr[3] = PACKET2(0);
	ib.ptr[4] = PACKET2(0);
	ib.ptr[5] = PACKET2(0);
	ib.ptr[6] = PACKET2(0);
	ib.ptr[7] = PACKET2(0);
	ib.length_dw = 8;
	r = radeon_ib_schedule(rdev, &ib, NULL, false);
	if (r) {
		DRM_ERROR("radeon: failed to schedule ib (%d).\n", r);
		goto free_ib;
	}
	r = radeon_fence_wait(ib.fence, false);
	if (r) {
		DRM_ERROR("radeon: fence wait failed (%d).\n", r);
		goto free_ib;
	}
	for (i = 0; i < rdev->usec_timeout; i++) {
		tmp = RREG32(scratch);
		if (tmp == 0xDEADBEEF) {
			break;
		}
		DRM_UDELAY(1);
	}
	if (i < rdev->usec_timeout) {
		DRM_INFO("ib test succeeded in %u usecs\n", i);
	} else {
		DRM_ERROR("radeon: ib test failed (scratch(0x%04X)=0x%08X)\n",
			  scratch, tmp);
		r = -EINVAL;
	}
free_ib:
	radeon_ib_free(rdev, &ib);
free_scratch:
	radeon_scratch_free(rdev, scratch);
	return r;
}
