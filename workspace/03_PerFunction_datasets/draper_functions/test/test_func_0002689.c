uvc_v4l2_put_xu_mapping(const struct uvc_xu_control_mapping *kp,
			struct uvc_xu_control_mapping32 __user *up)
{
	struct uvc_menu_info __user *umenus;
	struct uvc_menu_info __user *kmenus = kp->menu_info;
	compat_caddr_t p;

	if (!access_ok(VERIFY_WRITE, up, sizeof(*up)) ||
	    __copy_to_user(up, kp, offsetof(typeof(*up), menu_info)) ||
	    __put_user(kp->menu_count, &up->menu_count))
		return -EFAULT;

	if (__clear_user(up->reserved, sizeof(up->reserved)))
		return -EFAULT;

	if (kp->menu_count == 0)
		return 0;

	if (get_user(p, &up->menu_info))
		return -EFAULT;
	umenus = compat_ptr(p);

	if (copy_in_user(umenus, kmenus, kp->menu_count * sizeof(*umenus)))
		return -EFAULT;

	return 0;
}
