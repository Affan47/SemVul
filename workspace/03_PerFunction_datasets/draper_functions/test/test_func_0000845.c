cache_read_string(FILE *fp)
{
    static size_t   buflen;
    static char     *buf;
    size_t          len;

    if (fread_sane(fp, &len, sizeof(len)))
        return 0;
    if (len > buflen)
    {
        buflen = (len + 0xFF) & ~0xFF;
        buf = mem_change_size(buf, buflen);
    }
    if (fread_sane(fp, buf, len))
        return 0;
    return str_n_from_c(buf, len);
}
