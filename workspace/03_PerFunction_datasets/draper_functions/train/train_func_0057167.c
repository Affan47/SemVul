radeon_fence_wait_next(struct radeon_device *rdev, int ring)
{
	uint64_t seq[RADEON_NUM_RINGS] = {};
	long r;

	seq[ring] = atomic64_read(&rdev->fence_drv[ring].last_seq) + 1ULL;
	if (seq[ring] >= rdev->fence_drv[ring].sync_seq[ring]) {


		return -ENOENT;
	}
	r = radeon_fence_wait_seq_timeout(rdev, seq, false, MAX_SCHEDULE_TIMEOUT);
	if (r < 0)
		return r;
	return 0;
}
