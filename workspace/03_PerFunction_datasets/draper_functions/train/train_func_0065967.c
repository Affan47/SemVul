amdgpu_sa_bo_free(struct amdgpu_device *adev, struct amdgpu_sa_bo **sa_bo,
		       struct fence *fence)
{
	struct amdgpu_sa_manager *sa_manager;

	if (sa_bo == NULL || *sa_bo == NULL) {
		return;
	}

	sa_manager = (*sa_bo)->manager;
	spin_lock(&sa_manager->wq.lock);
	if (fence && !fence_is_signaled(fence)) {
		uint32_t idx;
		(*sa_bo)->fence = fence_get(fence);
		idx = amdgpu_ring_from_fence(fence)->idx;
		list_add_tail(&(*sa_bo)->flist, &sa_manager->flist[idx]);
	} else {
		amdgpu_sa_bo_remove_locked(*sa_bo);
	}
	wake_up_all_locked(&sa_manager->wq);
	spin_unlock(&sa_manager->wq.lock);
	*sa_bo = NULL;
}
