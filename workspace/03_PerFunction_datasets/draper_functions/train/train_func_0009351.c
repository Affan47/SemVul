__ww_mutex_lock(struct ww_mutex *lock, struct ww_acquire_ctx *ctx)
{
	int ret;

	might_sleep();
	ret =  __mutex_lock_common(&lock->base, TASK_UNINTERRUPTIBLE,
				   0, &ctx->dep_map, _RET_IP_, ctx, 1);
	if (!ret && ctx->acquired > 1)
		return ww_mutex_deadlock_injection(lock, ctx);

	return ret;
}
