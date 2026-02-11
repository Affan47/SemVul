uvc_v4l2_get_xu_query(struct uvc_xu_control_query *kp,
			const struct uvc_xu_control_query32 __user *up)
{
	u8 __user *udata;
	u8 __user *kdata;
	compat_caddr_t p;

	if (!access_ok(VERIFY_READ, up, sizeof(*up)) ||
	    __copy_from_user(kp, up, offsetof(typeof(*up), data)))
		return -EFAULT;

	if (kp->size == 0) {
		kp->data = NULL;
		return 0;
	}

	if (__get_user(p, &up->data))
		return -EFAULT;
	udata = compat_ptr(p);
	if (!access_ok(VERIFY_READ, udata, kp->size))
		return -EFAULT;

	kdata = compat_alloc_user_space(kp->size);
	if (kdata == NULL)
		return -EFAULT;
	kp->data = kdata;

	if (copy_in_user(kdata, udata, kp->size))
		return -EFAULT;

	return 0;
}
