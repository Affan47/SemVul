drmGetBusid(int fd)
{
    drm_unique_t u;

    memclear(u);

    if (drmIoctl(fd, DRM_IOCTL_GET_UNIQUE, &u))
	return NULL;
    u.unique = drmMalloc(u.unique_len + 1);
    if (drmIoctl(fd, DRM_IOCTL_GET_UNIQUE, &u))
	return NULL;
    u.unique[u.unique_len] = '\0';

    return u.unique;
}
