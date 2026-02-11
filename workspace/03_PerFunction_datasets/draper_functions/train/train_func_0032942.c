reservation_object_add_shared_inplace(struct reservation_object *obj,
				      struct reservation_object_list *fobj,
				      struct fence *fence)
{
	u32 i;

	fence_get(fence);

	preempt_disable();
	write_seqcount_begin(&obj->seq);

	for (i = 0; i < fobj->shared_count; ++i) {
		struct fence *old_fence;

		old_fence = rcu_dereference_protected(fobj->shared[i],
						reservation_object_held(obj));

		if (old_fence->context == fence->context) {

			RCU_INIT_POINTER(fobj->shared[i], fence);
			write_seqcount_end(&obj->seq);
			preempt_enable();

			fence_put(old_fence);
			return;
		}
	}


	RCU_INIT_POINTER(fobj->shared[fobj->shared_count], fence);
	fobj->shared_count++;

	write_seqcount_end(&obj->seq);
	preempt_enable();
}
