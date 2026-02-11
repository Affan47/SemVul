amdgpu_sync_wait(struct amdgpu_sync *sync)
{
	struct amdgpu_sync_entry *e;
	struct hlist_node *tmp;
	int i, r;

	hash_for_each_safe(sync->fences, i, tmp, e, node) {
		r = fence_wait(e->fence, false);
		if (r)
			return r;

		hash_del(&e->node);
		fence_put(e->fence);
		kfree(e);
	}

	if (amdgpu_enable_semaphores)
		return 0;

	for (i = 0; i < AMDGPU_MAX_RINGS; ++i) {
		struct fence *fence = sync->sync_to[i];
		if (!fence)
			continue;

		r = fence_wait(fence, false);
		if (r)
			return r;
	}

	return 0;
}
