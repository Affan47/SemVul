drmSetInterfaceVersion(int fd, drmSetVersion *version)
{
    int retcode = 0;
    drm_set_version_t sv;

    memclear(sv);
    sv.drm_di_major = version->drm_di_major;
    sv.drm_di_minor = version->drm_di_minor;
    sv.drm_dd_major = version->drm_dd_major;
    sv.drm_dd_minor = version->drm_dd_minor;

    if (drmIoctl(fd, DRM_IOCTL_SET_VERSION, &sv)) {
	retcode = -errno;
    }

    version->drm_di_major = sv.drm_di_major;
    version->drm_di_minor = sv.drm_di_minor;
    version->drm_dd_major = sv.drm_dd_major;
    version->drm_dd_minor = sv.drm_dd_minor;

    return retcode;
}
