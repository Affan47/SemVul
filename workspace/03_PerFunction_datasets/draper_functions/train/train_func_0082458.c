drmGetVersion(int fd)
{
    drmVersionPtr retval;
    drm_version_t *version = drmMalloc(sizeof(*version));

    version->name_len    = 0;
    version->name        = NULL;
    version->date_len    = 0;
    version->date        = NULL;
    version->desc_len    = 0;
    version->desc        = NULL;

    if (drmIoctl(fd, DRM_IOCTL_VERSION, version)) {
	drmFreeKernelVersion(version);
	return NULL;
    }

    if (version->name_len)
	version->name    = drmMalloc(version->name_len + 1);
    if (version->date_len)
	version->date    = drmMalloc(version->date_len + 1);
    if (version->desc_len)
	version->desc    = drmMalloc(version->desc_len + 1);

    if (drmIoctl(fd, DRM_IOCTL_VERSION, version)) {
	drmMsg("DRM_IOCTL_VERSION: %s\n", strerror(errno));
	drmFreeKernelVersion(version);
	return NULL;
    }


    if (version->name_len) version->name[version->name_len] = '\0';
    if (version->date_len) version->date[version->date_len] = '\0';
    if (version->desc_len) version->desc[version->desc_len] = '\0';

    retval = drmMalloc(sizeof(*retval));
    drmCopyVersion(retval, version);
    drmFreeKernelVersion(version);
    return retval;
}
