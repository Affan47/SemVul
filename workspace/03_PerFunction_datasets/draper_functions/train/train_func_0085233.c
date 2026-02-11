scbuf_peek_line (scbuf_t src, char *dstbuf, int len, int lines)
{
    int n, m, l;
    char *pdst;

    assert (src != NULL);

    if ((dstbuf == NULL) || (len < 0) || (lines < -1)) {
        errno = EINVAL;
        return (-1);
    }
    if (lines == 0) {
        return (0);
    }
    scbuf_mutex_lock (src);
    assert (scbuf_is_valid (src));
    n = scbuf_find_unread_line (src, len - 1, &lines);
    if (n > 0) {
        if (len > 0) {
            m = MIN (n, len - 1);
            if (m > 0) {
                pdst = dstbuf;
                l = scbuf_reader (src, m, (scbuf_iof) scbuf_put_mem, &pdst);
                assert (l == m);
            }
            assert (m < len);
            dstbuf[m] = '\0';
        }
    }
    assert (scbuf_is_valid (src));
    scbuf_mutex_unlock (src);
    return (n);
}
