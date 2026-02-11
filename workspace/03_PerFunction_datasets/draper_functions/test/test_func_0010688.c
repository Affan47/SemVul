drm_atomic_helper_suspend(struct drm_device *dev)
{
	struct drm_modeset_acquire_ctx ctx;
	struct drm_atomic_state *state;
	int err;

	drm_modeset_acquire_init(&ctx, 0);

retry:
	err = drm_modeset_lock_all_ctx(dev, &ctx);
	if (err < 0) {
		state = ERR_PTR(err);
		goto unlock;
	}

	state = drm_atomic_helper_duplicate_state(dev, &ctx);
	if (IS_ERR(state))
		goto unlock;

	err = drm_atomic_helper_disable_all(dev, &ctx);
	if (err < 0) {
		drm_atomic_state_free(state);
		state = ERR_PTR(err);
		goto unlock;
	}

unlock:
	if (PTR_ERR(state) == -EDEADLK) {
		drm_modeset_backoff(&ctx);
		goto retry;
	}

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
	return state;
}
