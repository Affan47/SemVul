source_esc_cb(wchar_t ch, char **dest, size_t *len)
{
    char buf[7];
    size_t copylen;


    sprintf(buf, "\\u%04x", (unsigned int)ch);


    copylen = 6;
    if (copylen > *len)
        copylen = *len;


    memcpy(*dest, buf, copylen);


    *dest += copylen;
    *len -= copylen;


    return 6;
}
