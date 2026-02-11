cik_compute_stop(struct radeon_device *rdev,
			     struct radeon_ring *ring)
{
	u32 j, tmp;

	cik_srbm_select(rdev, ring->me, ring->pipe, ring->queue, 0);

	tmp = RREG32(CP_PQ_WPTR_POLL_CNTL);
	tmp &= ~WPTR_POLL_EN;
	WREG32(CP_PQ_WPTR_POLL_CNTL, tmp);

	if (RREG32(CP_HQD_ACTIVE) & 1) {
		WREG32(CP_HQD_DEQUEUE_REQUEST, 1);
		for (j = 0; j < rdev->usec_timeout; j++) {
			if (!(RREG32(CP_HQD_ACTIVE) & 1))
				break;
			udelay(1);
		}
		WREG32(CP_HQD_DEQUEUE_REQUEST, 0);
		WREG32(CP_HQD_PQ_RPTR, 0);
		WREG32(CP_HQD_PQ_WPTR, 0);
	}
	cik_srbm_select(rdev, 0, 0, 0, 0);
}
