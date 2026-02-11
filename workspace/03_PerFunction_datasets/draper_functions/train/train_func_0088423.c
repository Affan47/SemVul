nouveau_fence_signal(struct nouveau_fence *fence)
{
	int drop = 0;

	fence_signal_locked(&fence->base);
	list_del(&fence->head);
	rcu_assign_pointer(fence->channel, NULL);

	if (test_bit(FENCE_FLAG_USER_BITS, &fence->base.flags)) {
		struct nouveau_fence_chan *fctx = nouveau_fctx(fence);

		if (!--fctx->notify_ref)
			drop = 1;
	}

	fence_put(&fence->base);
	return drop;
}
