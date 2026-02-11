amdgpu_ring_from_fence(struct fence *f)
{
	struct amdgpu_fence *a_fence;
	struct amd_sched_fence *s_fence;

	s_fence = to_amd_sched_fence(f);
	if (s_fence)
		return container_of(s_fence->sched, struct amdgpu_ring, sched);

	a_fence = to_amdgpu_fence(f);
	if (a_fence)
		return a_fence->ring;

	return NULL;
}
