slapi_create_dn_string(const char *fmt, ...)
{
    char *src = NULL;
    char *dest = NULL;
    size_t dest_len = 0;
    va_list ap;
    int rc = 0;

    if (NULL == fmt) {
        return NULL;
    }

    va_start(ap, fmt);
    src = PR_vsmprintf(fmt, ap);
    va_end(ap);

    rc = slapi_dn_normalize_ext(src, strlen(src), &dest, &dest_len);
    if (rc < 0) {
        slapi_ch_free_string(&src);
        return NULL;
    } else if (rc == 0) {
        *(dest + dest_len) = '\0';
    } else {
        slapi_ch_free_string(&src);
    }
    return dest;
}
