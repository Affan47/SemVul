compat_mga_init(struct file *file, unsigned int cmd,
			   unsigned long arg)
{
	drm_mga_init32_t init32;
	drm_mga_init_t __user *init;
	int err = 0, i;

	if (copy_from_user(&init32, (void __user *)arg, sizeof(init32)))
		return -EFAULT;

	init = compat_alloc_user_space(sizeof(*init));
	if (!access_ok(VERIFY_WRITE, init, sizeof(*init))
	    || __put_user(init32.func, &init->func)
	    || __put_user(init32.sarea_priv_offset, &init->sarea_priv_offset)
	    || __put_user(init32.chipset, &init->chipset)
	    || __put_user(init32.sgram, &init->sgram)
	    || __put_user(init32.maccess, &init->maccess)
	    || __put_user(init32.fb_cpp, &init->fb_cpp)
	    || __put_user(init32.front_offset, &init->front_offset)
	    || __put_user(init32.front_pitch, &init->front_pitch)
	    || __put_user(init32.back_offset, &init->back_offset)
	    || __put_user(init32.back_pitch, &init->back_pitch)
	    || __put_user(init32.depth_cpp, &init->depth_cpp)
	    || __put_user(init32.depth_offset, &init->depth_offset)
	    || __put_user(init32.depth_pitch, &init->depth_pitch)
	    || __put_user(init32.fb_offset, &init->fb_offset)
	    || __put_user(init32.mmio_offset, &init->mmio_offset)
	    || __put_user(init32.status_offset, &init->status_offset)
	    || __put_user(init32.warp_offset, &init->warp_offset)
	    || __put_user(init32.primary_offset, &init->primary_offset)
	    || __put_user(init32.buffers_offset, &init->buffers_offset))
		return -EFAULT;

	for (i = 0; i < MGA_NR_TEX_HEAPS; i++) {
		err |=
		    __put_user(init32.texture_offset[i],
			       &init->texture_offset[i]);
		err |=
		    __put_user(init32.texture_size[i], &init->texture_size[i]);
	}
	if (err)
		return -EFAULT;

	return drm_ioctl(file, DRM_IOCTL_MGA_INIT, (unsigned long)init);
}
