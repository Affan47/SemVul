amdgpu_bo_fence(struct amdgpu_bo *bo, struct fence *fence,
		     bool shared)
{
	struct reservation_object *resv = bo->tbo.resv;

	if (shared)
		reservation_object_add_shared_fence(resv, fence);
	else
		reservation_object_add_excl_fence(resv, fence);
}
