compat_drm_getsareactx(struct file *file, unsigned int cmd,
				  unsigned long arg)
{
	struct drm_ctx_priv_map __user *request;
	drm_ctx_priv_map32_t __user *argp = (void __user *)arg;
	int err;
	unsigned int ctx_id;
	void *handle;

	if (!access_ok(VERIFY_WRITE, argp, sizeof(*argp))
	    || __get_user(ctx_id, &argp->ctx_id))
		return -EFAULT;

	request = compat_alloc_user_space(sizeof(*request));
	if (!request)
		return -EFAULT;
	if (__put_user(ctx_id, &request->ctx_id))
		return -EFAULT;

	err = drm_ioctl(file, DRM_IOCTL_GET_SAREA_CTX, (unsigned long)request);
	if (err)
		return err;

	if (__get_user(handle, &request->handle)
	    || __put_user((unsigned long)handle, &argp->handle))
		return -EFAULT;

	return 0;
}
