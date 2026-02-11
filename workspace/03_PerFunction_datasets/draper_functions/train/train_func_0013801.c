virt_readlink(const char *path, char *buf, size_t bsiz)
{
    int res;
    ventry *ve;
    char *avbuf;
    int errno_save = errno;

    res = av_get_ventry(path, 0, &ve);
    if(res == 0) {
        res = av_readlink(ve, &avbuf);
	if(res == 0) {
	    res = copy_readlink(buf, bsiz, avbuf);
	    av_free(avbuf);
	}
	av_free_ventry(ve);
    }
    if(res < 0) {
        errno = -res;
        return -1;
    }

    errno = errno_save;
    return res;
}
