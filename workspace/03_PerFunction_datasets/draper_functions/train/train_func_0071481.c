format0_fdselect_proc(const cff_data_t *data, unsigned p, unsigned pe, unsigned int i)
{
    int code;
    unsigned u;

    if ((code = card8(&u, data, p + i, pe)) < 0)
        return code;
    return (int)u;
}
