cmp_base(const char *p, const char *q, const Py_ssize_t *shape,
         const Py_ssize_t *pstrides, const Py_ssize_t *psuboffsets,
         const Py_ssize_t *qstrides, const Py_ssize_t *qsuboffsets,
         const char *fmt)
{
    Py_ssize_t i;
    int equal;

    for (i = 0; i < shape[0]; p+=pstrides[0], q+=qstrides[0], i++) {
        const char *xp = ADJUST_PTR(p, psuboffsets);
        const char *xq = ADJUST_PTR(q, qsuboffsets);
        equal = unpack_cmp(xp, xq, fmt);
        if (equal <= 0)
            return equal;
    }

    return 1;
}
