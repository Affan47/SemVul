drmAgpUnbind(int fd, drm_handle_t handle)
{
    drm_agp_binding_t b;

    b.handle = handle;
    b.offset = 0;
    if (drmIoctl(fd, DRM_IOCTL_AGP_UNBIND, &b))
	return -errno;
    return 0;
}
