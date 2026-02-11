cbuf_writer (cbuf_t dst, int len, cbuf_iof getf, void *src, int *ndropped)
{


    int nfree, nleft, nrepl, n, m;
    int i_dst;

    assert(dst != NULL);
    assert(len > 0);
    assert(getf != NULL);
    assert(src != NULL);
    assert(cbuf_mutex_is_locked(dst));


    nfree = dst->size - dst->used;
    if ((len > nfree) && (dst->size < dst->maxsize)) {
        nfree += cbuf_grow(dst, len - nfree);
    }


    if (dst->overwrite == CBUF_NO_DROP) {
        len = MIN(len, dst->size - dst->used);
        if (len == 0) {
            errno = ENOSPC;
            return(-1);
        }
    }
    else if (dst->overwrite == CBUF_WRAP_ONCE) {
        len = MIN(len, dst->size);
    }


    i_dst = dst->i_in;
    nleft = len;
    m = 0;
    while (nleft > 0) {
        n = MIN(nleft, (dst->size + 1) - i_dst);
        m = getf(&dst->data[i_dst], src, n);
        if (m > 0) {
            nleft -= m;
            i_dst = (i_dst + m) % (dst->size + 1);
        }
        if (n != m) {
            break;
        }
    }


    n = len - nleft;
    assert((n >= 0) && (n <= len));


    if (n == 0) {
        return(m);
    }


    if (n > 0) {
        nrepl = (dst->i_out - dst->i_rep + (dst->size + 1)) % (dst->size + 1);
        dst->used = MIN(dst->used + n, dst->size);
        assert(i_dst == (dst->i_in + n) % (dst->size + 1));
        dst->i_in = i_dst;
        if (n > nfree - nrepl) {
            dst->got_wrap = 1;
            dst->i_rep = (dst->i_in + 1) % (dst->size + 1);
        }
        if (n > nfree) {
            dst->i_out = dst->i_rep;
        }
    }
    if (ndropped) {
        *ndropped = MAX(0, n - nfree);
    }
    return(n);
}
