amdgpu_fence_count_emitted(struct amdgpu_ring *ring)
{
	uint64_t emitted;


	amdgpu_fence_process(ring);
	emitted = ring->fence_drv.sync_seq[ring->idx]
		- atomic64_read(&ring->fence_drv.last_seq);

	if (emitted > 0x10000000)
		emitted = 0x10000000;

	return (unsigned)emitted;
}
