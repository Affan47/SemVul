np_uint(char *p, PyObject *v, const formatdef *f)
{
    unsigned long x;
    unsigned int y;
    if (get_ulong(v, &x) < 0)
        return -1;
    y = (unsigned int)x;
#if (SIZEOF_LONG > SIZEOF_INT)
    if (x > ((unsigned long)UINT_MAX))
        RANGE_ERROR(y, f, 1, -1);
#endif
    memcpy(p, (char *)&y, sizeof y);
    return 0;
}
