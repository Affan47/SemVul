gz_next4(state, ret)
    gz_statep state;
    unsigned long *ret;
{
    int ch;
    unsigned long val;
    z_streamp strm = &(state->strm);

    val = NEXT();
    val += (unsigned)NEXT() << 8;
    val += (unsigned long)NEXT() << 16;
    ch = NEXT();
    if (ch == -1)
        return -1;
    val += (unsigned long)ch << 24;
    *ret = val;
    return 0;
}
