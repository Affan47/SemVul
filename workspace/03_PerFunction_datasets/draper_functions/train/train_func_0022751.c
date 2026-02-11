drmGetCap(int fd, uint64_t capability, uint64_t *value)
{
	struct drm_get_cap cap = { capability, 0 };
	int ret;

	ret = drmIoctl(fd, DRM_IOCTL_GET_CAP, &cap);
	if (ret)
		return ret;

	*value = cap.value;
	return 0;
}
