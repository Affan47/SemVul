cbuf_replay_line (cbuf_t src, char *dstbuf, int len, int lines)
{
    int n, m, l;
    int nl;
    char *pdst;

    assert (src != NULL);

    if ((dstbuf == NULL) || (len < 0) || (lines < -1)) {
        errno = EINVAL;
        return (-1);
    }
    if (lines == 0) {
        return (0);
    }
    cbuf_mutex_lock (src);
    assert (cbuf_is_valid (src));
    n = cbuf_find_replay_line (src, len - 1, &lines, &nl);
    if (n > 0) {
        if (len > 0) {
            assert ((nl == 0) || (nl == 1));
            m = MIN (n, len - 1 - nl);
            m = MAX (m, 0);
            if (m > 0) {
                pdst = dstbuf;
                l = cbuf_replayer (src, m, (cbuf_iof) cbuf_put_mem, &pdst);
                assert (l == m);
            }


            if ((nl) && (len > 1)) {
                dstbuf[m++] = '\n';
            }
            assert (m < len);
            dstbuf[m] = '\0';
            n += nl;
        }
    }
    assert (cbuf_is_valid (src));
    cbuf_mutex_unlock (src);
    return (n);
}
