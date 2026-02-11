cmp_rec(const char *p, const char *q,
        Py_ssize_t ndim, const Py_ssize_t *shape,
        const Py_ssize_t *pstrides, const Py_ssize_t *psuboffsets,
        const Py_ssize_t *qstrides, const Py_ssize_t *qsuboffsets,
        char fmt, struct unpacker *unpack_p, struct unpacker *unpack_q)
{
    Py_ssize_t i;
    int equal;

    assert(ndim >= 1);
    assert(shape != NULL);
    assert(pstrides != NULL);
    assert(qstrides != NULL);

    if (ndim == 1) {
        return cmp_base(p, q, shape,
                        pstrides, psuboffsets,
                        qstrides, qsuboffsets,
                        fmt, unpack_p, unpack_q);
    }

    for (i = 0; i < shape[0]; p+=pstrides[0], q+=qstrides[0], i++) {
        const char *xp = ADJUST_PTR(p, psuboffsets);
        const char *xq = ADJUST_PTR(q, qsuboffsets);
        equal = cmp_rec(xp, xq, ndim-1, shape+1,
                        pstrides+1, psuboffsets ? psuboffsets+1 : NULL,
                        qstrides+1, qsuboffsets ? qsuboffsets+1 : NULL,
                        fmt, unpack_p, unpack_q);
        if (equal <= 0)
            return equal;
    }

    return 1;
}
