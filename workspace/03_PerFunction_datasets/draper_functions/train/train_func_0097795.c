drmMapBufs(int fd)
{
    drm_buf_map_t bufs;
    drmBufMapPtr  retval;
    int           i;

    bufs.count = 0;
    bufs.list  = NULL;
    bufs.virtual = NULL;
    if (drmIoctl(fd, DRM_IOCTL_MAP_BUFS, &bufs))
	return NULL;

    if (!bufs.count)
	return NULL;

	if (!(bufs.list = drmMalloc(bufs.count * sizeof(*bufs.list))))
	    return NULL;

	if (drmIoctl(fd, DRM_IOCTL_MAP_BUFS, &bufs)) {
	    drmFree(bufs.list);
	    return NULL;
	}

	retval = drmMalloc(sizeof(*retval));
	retval->count = bufs.count;
	retval->list  = drmMalloc(bufs.count * sizeof(*retval->list));
	for (i = 0; i < bufs.count; i++) {
	    retval->list[i].idx     = bufs.list[i].idx;
	    retval->list[i].total   = bufs.list[i].total;
	    retval->list[i].used    = 0;
	    retval->list[i].address = bufs.list[i].address;
	}

	drmFree(bufs.list);

	return retval;
}
