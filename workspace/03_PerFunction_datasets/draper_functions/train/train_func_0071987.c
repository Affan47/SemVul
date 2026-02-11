drm_legacy_unlock(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	struct drm_lock *lock = data;
	struct drm_master *master = file_priv->master;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return -EINVAL;

	if (lock->context == DRM_KERNEL_CONTEXT) {
		DRM_ERROR("Process %d using kernel context %d\n",
			  task_pid_nr(current), lock->context);
		return -EINVAL;
	}

	if (drm_legacy_lock_free(&master->lock, lock->context)) {

	}

	return 0;
}
