radeon_fence_read(struct radeon_device *rdev, int ring)
{
	struct radeon_fence_driver *drv = &rdev->fence_drv[ring];
	u32 seq = 0;

	if (likely(rdev->wb.enabled || !drv->scratch_reg)) {
		if (drv->cpu_addr) {
			seq = le32_to_cpu(*drv->cpu_addr);
		} else {
			seq = lower_32_bits(atomic64_read(&drv->last_seq));
		}
	} else {
		seq = RREG32(drv->scratch_reg);
	}
	return seq;
}
