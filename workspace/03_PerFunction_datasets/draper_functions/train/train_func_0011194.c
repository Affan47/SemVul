compat_radeon_cp_vertex2(struct file *file, unsigned int cmd,
				    unsigned long arg)
{
	drm_radeon_vertex2_32_t req32;
	drm_radeon_vertex2_t __user *request;

	if (copy_from_user(&req32, (void __user *)arg, sizeof(req32)))
		return -EFAULT;

	request = compat_alloc_user_space(sizeof(*request));
	if (!access_ok(VERIFY_WRITE, request, sizeof(*request))
	    || __put_user(req32.idx, &request->idx)
	    || __put_user(req32.discard, &request->discard)
	    || __put_user(req32.nr_states, &request->nr_states)
	    || __put_user((void __user *)(unsigned long)req32.state,
			  &request->state)
	    || __put_user(req32.nr_prims, &request->nr_prims)
	    || __put_user((void __user *)(unsigned long)req32.prim,
			  &request->prim))
		return -EFAULT;

	return drm_ioctl(file, DRM_IOCTL_RADEON_VERTEX2, (unsigned long)request);
}
