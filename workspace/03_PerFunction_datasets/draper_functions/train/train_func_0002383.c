ttm_bo_flush_all_fences(struct ttm_buffer_object *bo)
{
	struct reservation_object_list *fobj;
	struct fence *fence;
	int i;

	fobj = reservation_object_get_list(bo->resv);
	fence = reservation_object_get_excl(bo->resv);
	if (fence && !fence->ops->signaled)
		fence_enable_sw_signaling(fence);

	for (i = 0; fobj && i < fobj->shared_count; ++i) {
		fence = rcu_dereference_protected(fobj->shared[i],
					reservation_object_held(bo->resv));

		if (!fence->ops->signaled)
			fence_enable_sw_signaling(fence);
	}
}
