get_bytes(const char *path, unsigned char *outdata, int size)
{
    size_t len;
    int fd, ret = 1;

    if (path == NULL)
	path = egd_path;

    fd = connect_egd(path);
    if (fd < 0)
	return 0;

    while(size) {
	len = size;
	if (len > MAX_EGD_DATA)
	    len = MAX_EGD_DATA;
	ret = get_entropy(fd, outdata, len);
	if (ret != 1)
	    break;
	outdata += len;
	size -= len;
    }
    close(fd);

    return ret;
}
