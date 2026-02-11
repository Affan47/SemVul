drmOpenMinor(int minor, int create, int type)
{
    int  fd;
    char buf[64];

    if (create)
	return drmOpenDevice(makedev(DRM_MAJOR, minor), minor, type);

    sprintf(buf, type ? DRM_DEV_NAME : DRM_CONTROL_DEV_NAME, DRM_DIR_NAME, minor);
    if ((fd = open(buf, O_RDWR, 0)) >= 0)
	return fd;
    return -errno;
}
