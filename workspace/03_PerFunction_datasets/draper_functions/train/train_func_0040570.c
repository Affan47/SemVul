data_source_access_bytes(const gs_data_source_t * psrc, ulong start,
                         uint length, byte * buf, const byte ** ptr)
{
    const byte *p = psrc->data.str.data + start;

    if (ptr)
        *ptr = p;
    else
        memcpy(buf, p, length);
    return 0;
}
