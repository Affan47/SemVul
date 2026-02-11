cbuf_copy (cbuf_t src, cbuf_t dst, int len, int *ndropped)
{
    int n = 0;

    assert (src != NULL);
    assert (dst != NULL);

    if (ndropped) {
        *ndropped = 0;
    }
    if (src == dst) {
        errno = EINVAL;
        return (-1);
    }
    if (len < -1) {
        errno = EINVAL;
        return (-1);
    }
    if (len == 0) {
        return (0);
    }


    if (src < dst) {
        cbuf_mutex_lock (src);
        cbuf_mutex_lock (dst);
    }
    else {
        cbuf_mutex_lock (dst);
        cbuf_mutex_lock (src);
    }
    assert (cbuf_is_valid (src));
    assert (cbuf_is_valid (dst));

    if (len == -1) {
        len = src->used;
    }
    if (len > 0) {
        n = cbuf_copier (src, dst, len, ndropped);
    }
    assert (cbuf_is_valid (src));
    assert (cbuf_is_valid (dst));
    cbuf_mutex_unlock (src);
    cbuf_mutex_unlock (dst);
    return (n);
}
