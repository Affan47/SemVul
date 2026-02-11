amdgpu_gem_wait_idle_ioctl(struct drm_device *dev, void *data,
			      struct drm_file *filp)
{
	struct amdgpu_device *adev = dev->dev_private;
	union drm_amdgpu_gem_wait_idle *args = data;
	struct drm_gem_object *gobj;
	struct amdgpu_bo *robj;
	uint32_t handle = args->in.handle;
	unsigned long timeout = amdgpu_gem_timeout(args->in.timeout);
	int r = 0;
	long ret;

	gobj = drm_gem_object_lookup(dev, filp, handle);
	if (gobj == NULL) {
		return -ENOENT;
	}
	robj = gem_to_amdgpu_bo(gobj);
	if (timeout == 0)
		ret = reservation_object_test_signaled_rcu(robj->tbo.resv, true);
	else
		ret = reservation_object_wait_timeout_rcu(robj->tbo.resv, true, true, timeout);


	if (ret >= 0) {
		memset(args, 0, sizeof(*args));
		args->out.status = (ret == 0);
	} else
		r = ret;

	drm_gem_object_unreference_unlocked(gobj);
	r = amdgpu_gem_handle_lockup(adev, r);
	return r;
}
