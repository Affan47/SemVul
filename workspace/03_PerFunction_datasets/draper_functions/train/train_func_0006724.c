drmMap(int fd, drm_handle_t handle, drmSize size, drmAddressPtr address)
{
    static unsigned long pagesize_mask = 0;

    if (fd < 0)
	return -EINVAL;

    if (!pagesize_mask)
	pagesize_mask = getpagesize() - 1;

    size = (size + pagesize_mask) & ~pagesize_mask;

    *address = mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, handle);
    if (*address == MAP_FAILED)
	return -errno;
    return 0;
}
