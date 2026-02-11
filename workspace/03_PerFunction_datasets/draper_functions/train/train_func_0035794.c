drmRmMap(int fd, drm_handle_t handle)
{
    drm_map_t map;

    map.handle = (void *)(uintptr_t)handle;

    if(drmIoctl(fd, DRM_IOCTL_RM_MAP, &map))
	return -errno;
    return 0;
}
