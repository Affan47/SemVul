vmw_generic_ioctl(struct file *filp, unsigned int cmd,
			      unsigned long arg,
			      long (*ioctl_func)(struct file *, unsigned int,
						 unsigned long))
{
	struct drm_file *file_priv = filp->private_data;
	struct drm_device *dev = file_priv->minor->dev;
	unsigned int nr = DRM_IOCTL_NR(cmd);
	struct vmw_master *vmaster;
	unsigned int flags;
	long ret;


	if ((nr >= DRM_COMMAND_BASE) && (nr < DRM_COMMAND_END)
	    && (nr < DRM_COMMAND_BASE + dev->driver->num_ioctls)) {
		const struct drm_ioctl_desc *ioctl =
			&vmw_ioctls[nr - DRM_COMMAND_BASE];

		if (nr == DRM_COMMAND_BASE + DRM_VMW_EXECBUF) {
			ret = (long) drm_ioctl_permit(ioctl->flags, file_priv);
			if (unlikely(ret != 0))
				return ret;

			if (unlikely((cmd & (IOC_IN | IOC_OUT)) != IOC_IN))
				goto out_io_encoding;

			return (long) vmw_execbuf_ioctl(dev, arg, file_priv,
							_IOC_SIZE(cmd));
		}

		if (unlikely(ioctl->cmd != cmd))
			goto out_io_encoding;

		flags = ioctl->flags;
	} else if (!drm_ioctl_flags(nr, &flags))
		return -EINVAL;

	vmaster = vmw_master_check(dev, file_priv, flags);
	if (IS_ERR(vmaster)) {
		ret = PTR_ERR(vmaster);

		if (ret != -ERESTARTSYS)
			DRM_INFO("IOCTL ERROR Command %d, Error %ld.\n",
				 nr, ret);
		return ret;
	}

	ret = ioctl_func(filp, cmd, arg);
	if (vmaster)
		ttm_read_unlock(&vmaster->lock);

	return ret;

out_io_encoding:
	DRM_ERROR("Invalid command format, ioctl %d\n",
		  nr - DRM_COMMAND_BASE);

	return -EINVAL;
}
