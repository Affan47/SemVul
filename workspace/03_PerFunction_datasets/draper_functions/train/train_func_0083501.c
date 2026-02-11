ws_f_memdup(WsFastMalloc *pool, const void *ptr, size_t size)
{
    unsigned char *d = ws_f_malloc(pool, size + 1);

    if (d == NULL)
        return NULL;

    memcpy(d, ptr, size);
    d[size] = '\0';

    return d;
}
